#!/usr/bin/env python3

# Cannon simulation code for IEE2613
# Martin Andrighetti, 2023

from dataclasses import dataclass, field
import math
import pygame as pg
import numpy as np
import sys

# Graphical parameters
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

FONTSIZE = 16


@dataclass
class Frame:
    id: int
    thresh: int
    user: int
    left: int
    right: int


N: int
K: int
T: int
R: int
S0: np.ndarray
D: np.ndarray
J: int
F: list[Frame]


def parse_data(data: str):
    """
    Parse data.
    """
    global N, K, T, R, S0, D, J, F, P

    args = data.split()

    def consume_float(n: int) -> list[float]:
        nonlocal args
        x = args[:n]
        args = args[n:]
        return list(map(float, x))

    def consume_int(n: int) -> list[int]:
        nonlocal args
        x = args[:n]
        args = args[n:]
        return list(map(int, x))

    N, K, T, R = consume_int(4)
    S0 = np.array(consume_float(T * K * R * N)).reshape((T, K, R, N))
    D = np.array(consume_float(K * R * N * N)).reshape((K, R, N, N))
    (J,) = consume_int(1)
    F = []
    for j in range(J):
        j2, thresh, user, left, delta = consume_int(5)
        assert j == j2
        F.append(Frame(id=j, thresh=thresh, user=user, left=left, right=left + delta))
    if len(args) > 0:
        P = np.array(consume_float(T * K * R * N)).reshape((T, K, R, N))
    else:
        P = np.zeros((T, K, R, N))
    assert len(args) == 0


parse_data(sys.stdin.read())
W = 192 / math.log(2)
THRESH: np.ndarray = np.array([f.thresh / W for f in F])


PERTIME: list[list[int]] = [[] for t in range(T)]
for f in F:
    for t in range(f.left, f.right):
        PERTIME[t].append(f.id)


@dataclass
class Score:
    frames: int = 0
    G: np.ndarray = np.zeros(J)
    bycell: np.ndarray = np.zeros((T, K, N))
    logsum: np.ndarray = np.zeros((T, K, N))
    rcount: np.ndarray = np.zeros((T, K, N))
    logcontrib: np.ndarray = np.zeros((T, K, R, N))
    active: np.ndarray = np.zeros((T, K, R, N))

    def update(self, t: int, r: int):
        # Remove affected cell scores from frames scores
        for j in PERTIME[t]:
            n = F[j].user
            for k in range(K):
                self.G[j] -= self.bycell[t, k, n]

        # Remove individual point scores from cell scores
        self.rcount[t, :, :] -= self.active[t, :, r, :]
        self.logsum[t, :, :] -= self.logcontrib[t, :, r, :]

        # Recompute point scores for all points in the affected band
        for j in PERTIME[t]:
            n = F[j].user
            for k in range(K):
                if P[t, k, r, n] != 0:
                    column = P[t, k, r, :] != 0
                    column[n] = 0
                    interf1 = np.sum(column * D[k, r, n, :])

                    mat = np.ones((K, N))
                    mat[k, :] = 0
                    mat[:, n] = 0
                    interf2 = np.sum(
                        mat
                        * np.expand_dims(S0[t, :, r, n], 1)
                        * P[t, :, r, :]
                        * np.exp(-D[:, r, n, :])
                    )

                    self.logcontrib[t, k, r, n] = (
                        np.log(S0[t, k, r, n] * P[t, k, r, n] / (1 + interf2)) + interf1
                    )
                    self.active[t, k, r, n] = 1
                else:
                    self.logcontrib[t, k, r, n] = 0
                    self.active[t, k, r, n] = 0

        # Re-add individual point scores to cell scores
        self.rcount[t, :, :] += self.active[t, :, r, :]
        self.logsum[t, :, :] += self.logcontrib[t, :, r, :]

        # Recompute and re-add cell scores to frame scores
        for j in PERTIME[t]:
            n = F[j].user
            for k in range(K):
                rcount = self.rcount[t, k, n]
                logsum = self.logsum[t, k, n]
                self.bycell[t, k, n] = 0
                if rcount:
                    self.bycell[t, k, n] = rcount * np.log1p(np.exp(logsum / rcount))
                self.G[j] += self.bycell[t, k, n]

        # Recompute the number of frames over the threshold
        self.frames = np.sum(self.G >= THRESH)


SCORE = Score()
for t in range(T):
    for r in range(R):
        SCORE.update(t, r)


def setp(t: int, k: int, r: int, n: int, p: float):
    if p == P[t, k, r, n]:
        return
    P[t, k, r, n] = p
    SCORE.update(t, r)


def set_and_redistribute_p(t: int, k: int, r: int, n: int, p: bool):
    if (P[t, k, r, n] != 0) == p:
        return
    P[t, k, r, n] = float(p)

    free_power = R
    free_active = np.sum(P[t, k, :, :] != 0)
    free_bands = np.ones(R, dtype=bool)
    while free_active > 0:
        for r in range(R):
            if free_bands[r]:
                active_in_band = np.sum(P[t, k, r, :] != 0)
                if free_power / free_active * active_in_band > 4:
                    # The power in this band is bottlenecked by the band power limit
                    P[t, k, r, :][P[t, k, r, :] != 0] = 4 / active_in_band
                    free_power -= 4
                    free_active -= active_in_band
                    free_bands[r] = False
                    break
        else:
            # All bands normalized, distribute remaining power
            for r in range(R):
                if free_bands[r]:
                    P[t, k, r, :][P[t, k, r, :] != 0] = free_power / free_active
            break

    for r in range(R):
        SCORE.update(t, r)


def drawtext(
    scr: pg.Surface,
    txt: str,
    pos: tuple[int, int],
    color: tuple[int, int, int] = (255, 255, 255),
):
    scr.blit(FONT.render(txt, True, color), pos)


@dataclass
class TextRenderer:
    scr: pg.Surface
    x: int
    y: int
    align: float = 0

    def print(self, txt: str, color: tuple[int, int, int] = (255, 255, 255)):
        drawtext(
            self.scr, txt, (self.x - self.align * FONT.size(txt)[0], self.y), color
        )
        self.y += FONTSIZE

    def relocate(self, pos: tuple[int, int]):
        self.x = pos[0]
        self.y = pos[1]


class Mode:
    axes: str

    def __init__(self, axes: str):
        assert len(axes) == 4
        self.axes = axes
        self.x_max = self.axis_size(axes[0]) - 1
        self.y_max = self.axis_size(axes[1]) - 1
        self.hover = None

    def axis_index(self, axis: str) -> int:
        return self.axes.index(axis)

    def known_axes(self) -> tuple[int | None, int | None, int | None, int | None]:
        return (
            app.get_axis(self.axes[0]),
            app.get_axis(self.axes[1]),
            app.get_axis(self.axes[2]),
            app.get_axis(self.axes[3]),
        )

    def axis_size(self, axis: str):
        if axis == "t":
            return T
        elif axis == "k":
            return K
        elif axis == "r":
            return R
        elif axis == "n":
            return len(PERTIME[app.t])

    def map_axes(self, x: tuple[int, int, int, int]) -> tuple[int, int, int, int]:
        y = {}
        for i, c in enumerate(self.axes):
            y[c] = x[i]
        return y["t"], y["k"], y["r"], y["n"]

    def onkey(self, key: int, is_down: bool):
        down = pg.key.get_pressed()
        if is_down:
            if key == pg.K_a:
                app.mode = MODES[(MODES.index(app.mode) + 1) % len(MODES)]
            if key == pg.K_q:
                app.submodes[app.mode] = SUBMODES[app.mode][
                    (SUBMODES[app.mode].index(app.submodes[app.mode]) + 1)
                    % len(SUBMODES[app.mode])
                ]

            d = 1
            if down[pg.K_LSHIFT] or down[pg.K_RSHIFT]:
                d = 10
            if down[pg.K_LCTRL] or down[pg.K_RCTRL]:
                d = 100
            if key == pg.K_LEFT:
                app.set_axis(self.axes[0], max(app.get_axis(self.axes[0]) - d, 0))
            if key == pg.K_RIGHT:
                app.set_axis(
                    self.axes[0],
                    min(
                        app.get_axis(self.axes[0]) + d, self.axis_size(self.axes[0]) - 1
                    ),
                )
            if key == pg.K_DOWN:
                app.set_axis(self.axes[1], max(app.get_axis(self.axes[1]) - d, 0))
            if key == pg.K_UP:
                app.set_axis(
                    self.axes[1],
                    min(
                        app.get_axis(self.axes[1]) + d, self.axis_size(self.axes[1]) - 1
                    ),
                )

    def onmouse(self, x: float, y: float, button: int, is_down: bool):
        pass

    def draw(self, scr: pg.Surface, sz: np.ndarray):
        W, H = self.axis_size(self.axes[2]), self.axis_size(self.axes[3])

        pixelsize = np.round(sz * 0.6 / [W, H])
        fullsize = pixelsize * [W, H]

        def stretch(x: float, y: float) -> tuple[int, int]:
            return np.round(np.round(sz / 2 - fullsize / 2) + [x, y] * pixelsize)

        mouse_x, mouse_y = pg.mouse.get_pos()

        app.set_axis(self.axes[2], None)
        app.set_axis(self.axes[3], None)
        for y in range(H):
            for x in range(W):
                rect = pg.Rect(stretch(x, y), pixelsize)
                collide = rect.collidepoint(mouse_x, mouse_y)
                if collide:
                    app.set_axis(self.axes[2], x)
                    app.set_axis(self.axes[3], y)
                self.drawpixel(
                    scr,
                    rect,
                    collide,
                    (app.get_axis(self.axes[0]), app.get_axis(self.axes[1]), x, y),
                )

        txt = TextRenderer(scr=scr, x=10, y=10)

        for y in range(H):
            txt.relocate(stretch(0, y + 0.5) - [10, FONTSIZE])
            txt.align = 1
            self.label_axis(
                3,
                [
                    app.get_axis(self.axes[0]),
                    app.get_axis(self.axes[1]),
                    None,
                    y,
                ],
                txt,
            )
        for x in range(W):
            txt.relocate(stretch(x + 0.5, 0) - [0, 2 * FONTSIZE])
            txt.align = 0.5
            self.label_axis(
                2,
                [app.get_axis(self.axes[0]), app.get_axis(self.axes[1]), x, None],
                txt,
            )

        txt.relocate((10, 10))
        txt.align = 0
        self.draw_text(scr, txt)

    def drawpixel(
        self,
        scr: pg.Surface,
        rect: pg.Rect,
        collide: bool,
        values: tuple[int, int, int, int],
    ):
        t, k, r, jj = (
            values[self.axis_index("t")],
            values[self.axis_index("k")],
            values[self.axis_index("r")],
            values[self.axis_index("n")],
        )
        j = PERTIME[t][jj]
        n = F[j].user
        s0 = S0[t, k, r, n]
        p = P[t, k, r, n]

        v = round(128 + 40 * math.log10(s0))
        pg.draw.rect(scr, (v, v, v), rect)
        pg.draw.rect(scr, (v - 20, v - 20, v - 20), rect, width=1)
        if p != 0:
            a = 0.85
            h = p / 4
            prect = pg.Rect(
                rect.left, rect.top + rect.height * (1 - h), rect.width, rect.height * h
            )
            pg.draw.rect(scr, (v * a, v, v * a), prect)
            a = 1 if p == 0 else 0.9
        if collide:
            buts = pg.mouse.get_pressed()
            if (buts[0] and P[t, k, r, n] == 0) or (buts[2] and P[t, k, r, n] != 0):
                if True:
                    # Set P to nonzero, distributing power equally
                    set_and_redistribute_p(t, k, r, n, buts[0])
                else:
                    # Set all P to 1, disallowing more than the limit
                    kpower = np.sum(P[t, k, :, :]) - P[t, k, r, n]
                    rpower = np.sum(P[t, k, r, :]) - P[t, k, r, n]
                    p = min(p, 4 - rpower, R - kpower)
                    p = 1 if buts[0] else 0
                    setp(t, k, r, n, p)

    def draw_text(self, scr: pg.Surface, txt: TextRenderer):
        txt.print("S0(nk)")
        self.short_label_axis(0, txt)
        self.short_label_axis(1, txt)
        self.short_label_axis(2, txt)
        self.short_label_axis(3, txt)
        t, k, r, n = (
            app.get_axis("t"),
            app.get_axis("k"),
            app.get_axis("r"),
            app.get_axis("n"),
        )
        if t is not None and k is not None and r is not None and n is not None:
            hovertxt = f"{S0[t,k,r,n]}"
        else:
            hovertxt = ""
        txt.print(f"hovered s0: {hovertxt}")
        txt.print(f"score: {SCORE.frames}")

    def label_axis(self, axis_idx: int, values: list[int | None], txt: TextRenderer):
        axis = self.axes[axis_idx]
        if axis == "k":
            t = values[self.axis_index("t")]
            k = values[self.axis_index("k")]
            txt.print(f"k = {k}")
            txt.print(f"{round(np.sum(SCORE.bycell[t,k,:]), 2)}")
        elif axis == "r":
            r = values[self.axis_index("r")]
            txt.print(f"r = {r}")
        elif axis == "n":
            t = values[self.axis_index("t")]
            jj = values[axis_idx]
            j = PERTIME[t][jj]
            n = F[j].user
            bits = np.sum(SCORE.bycell[F[j].left : F[j].right, :, n])
            thresh = THRESH[j]

            txt.print(f"n = {n}")
            txt.print(
                f"{round(bits, 2)}/{round(thresh, 2)}",
                (190, 255, 190) if bits >= thresh else (255, 190, 190),
            )

    def short_label_axis(self, axis_idx: int, txt: TextRenderer):
        axis = self.axes[axis_idx]
        if axis_idx < 2:
            value = app.get_axis(axis)
            txt.print(f"{axis} = {value}/{self.axis_size(axis)}")
        else:
            screen_axis = "xy"[axis_idx - 2]
            txt.print(
                f"{screen_axis}-axis: {axis} ({axis.upper()} = {self.axis_size(axis)})"
            )


MODES = ["s0", "d"]
SUBMODES = {
    "s0": ["kn", "rn"],
    "d": ["nm"],
}


@dataclass
class State:
    t: int | None = 0
    k: int | None = 0
    r: int | None = 0
    n: int | None = 0

    mode: str = MODES[0]
    submodes: dict[str, str] = field(
        default_factory=lambda: {
            mode: submodes[0] for mode, submodes in SUBMODES.items()
        }
    )

    def set_axis(self, axis: str, value: int | None):
        assert len(axis) == 1
        assert hasattr(self, axis)
        setattr(self, axis, value)

    def get_axis(self, axis: str) -> int | None:
        assert len(axis) == 1
        return getattr(self, axis)


# App state
app_running = True
app = State()
app_mode = {
    "s0": {
        "kn": Mode("trnk"),
        "rn": Mode("tknr"),
    },
    "d": {
        "nm": Mode("rknn"),
    },
}


def draw_screen():
    """
    Redraw the screen with all necessary state.
    """
    scr = pg.display.get_surface()
    w, h = scr.get_rect().size

    # Draw background
    pg.draw.rect(scr, (0, 10, 20), scr.get_rect())

    # Draw mode
    app_mode[app.mode][app.submodes[app.mode]].draw(scr, np.array([w, h]))

    # Update display
    pg.display.flip()


def handle_key(key: int, is_down: bool):
    """
    Handle a single keypress/keyrelease.
    """
    global app_running, app_mode

    if is_down:
        if key == pg.K_ESCAPE:
            # Quit with escape
            app_running = False

    # Pass on to mode
    app_mode[app.mode][app.submodes[app.mode]].onkey(key, is_down)


def handle_mouse(button: int, is_down: bool):
    """
    Handle a single mouse click or release.
    """
    global app_target

    x, y = pg.mouse.get_pos()
    app_mode[app.mode][app.submodes[app.mode]].onmouse(x, y, button, is_down)


def handle_events():
    """
    Handle all the events for this frame.
    """
    global app_running
    for ev in pg.event.get():
        if ev.type == pg.QUIT:
            # Exit requested
            app_running = False
        elif ev.type == pg.KEYDOWN:
            handle_key(ev.key, True)
        elif ev.type == pg.KEYUP:
            handle_key(ev.key, False)
        elif ev.type == pg.MOUSEBUTTONDOWN:
            handle_mouse(ev.button, True)
        elif ev.type == pg.MOUSEBUTTONUP:
            handle_mouse(ev.button, False)


def init_window():
    """
    Setup the window for drawing.
    """
    global FONT
    pg.init()
    pg.display.set_caption("Huawei Visualize")
    pg.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pg.RESIZABLE)
    pg.key.set_repeat(500, 50)
    FONT = pg.font.SysFont("Arial", FONTSIZE)


def run_main():
    init_window()
    while app_running:
        handle_events()
        draw_screen()
    print("Goodbye")


if __name__ == "__main__":
    run_main()
