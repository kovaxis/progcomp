#!/usr/bin/env python3

import json
from pathlib import Path
import random
import string
import time
import requests
import re
import logging
import parse

logging.basicConfig(level=logging.INFO)
log = logging.getLogger()

handle, password = Path("scrape/credentials").read_text().split("\n")[0:2]

contest_id = "1885"
problem_id = "A"
language_id = "73"
filename = "b.cpp"

session = requests.session()

ftaa = "".join(random.choice(string.ascii_lowercase + string.digits) for _ in range(18))
btaa = "".join(random.choice(string.hexdigits) for _ in range(32))

login_page = session.get("https://codeforces.com/enter").content.decode("utf-8")

login_csrf = re.search(r"name='csrf_token' value='([^']+)", login_page).group(1)

session.post(
    "https://codeforces.com/enter",
    files={
        "csrf_token": (None, login_csrf),
        "action": (None, "enter"),
        "ftaa": (None, ftaa),
        "btaa": (None, btaa),
        "handleOrEmail": (None, handle),
        "password": (None, password),
        "_tta": (None, "655"),
        "remember": (None, "on"),
    },
).content.decode("utf-8")


def submit(file_source: str) -> str:
    log.info("submitting...")

    problem_page = session.get(
        f"https://codeforces.com/contest/{contest_id}/problem/{problem_id}",
    ).content.decode("utf-8")

    submit_csrf = re.search(r'\?csrf_token=([^"]+)', problem_page).group(1)

    sub_page = session.post(
        f"https://codeforces.com/contest/{contest_id}/problem/{problem_id}?csrf_token={submit_csrf}",
        data={
            "csrf_token": submit_csrf,
            "action": "submitSolutionFormSubmitted",
            "contestId": contest_id,
            "submittedProblemIndex": problem_id,
            "programTypeId": language_id,
            "ftaa": ftaa,
            "btaa": btaa,
            "source": file_source,
            "tabSize": "4",
            "_tta": "655",
            "sourceCodeConfirmed": "true",
        },
    ).content.decode("utf-8")

    if "You have submitted exactly the same code before" in sub_page:
        log.error("duplicate upload")
        return ""

    subs = re.findall(r'data-submission-id="(\d+)"', sub_page)

    sub_id = subs[0]
    sub_csrf = re.search(r"name='csrf_token' value='([^']+)", sub_page).group(1)

    log.info(f"uploaded as submission {sub_id}, waiting for judge...")
    time.sleep(5)
    while True:
        sub_data_json = session.post(
            "https://codeforces.com/data/judgeProtocol",
            data={
                "csrf_token": sub_csrf,
                "submissionId": sub_id,
            },
        ).content.decode("utf-8")
        sub_data = json.loads(sub_data_json)
        if sub_data == "Protocol is unavailable":
            log.info("still not ready, waiting...")
            time.sleep(5)
        else:
            log.info("judge answered")
            break

    return sub_data


base_mb = 45
template = Path(filename).read_text() + f" // {random.randint(0, 1000000000)}"
for percent in range(101):
    code = template.replace("123456789", str(percent / 100))
    ans_text = submit(code)
    ans = parse.parse(ans_text)
    for tc in ans:
        dval = (tc.mb - base_mb) / 900 * 2 - 2
        print(f"{dval},", end="")
    print()
