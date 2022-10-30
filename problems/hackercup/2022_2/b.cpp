#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1000000007;

// hackproof unordered map hash
struct Hash
{
    size_t operator()(const ll &x) const
    {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

struct Day
{
    // the buyers available at a day, sorted by buy price from higher to lower
    // this means that the "better buyers" are first
    // vector<Buyer> buyers;
    // keep track of the best paths starting at this day
    // if I sell at price Y on this day, a deal that buys at X and makes Z profit will produce:
    // X - Y + Z profit
    // this priority_queue stores only the X + Z term, because Y is defined by the buyer
    priority_queue<ll> deals;
};

struct Buyer
{
    ll buy_price;
    vector<ll> most_profit; // at most length K
};

// process days from last to first
// on any given day, process the highest price buys&sells, then the lower ones
// (this avoids a high price sell to match a low price buy)
// if both prices are the same, process the sells, then the buys
// (this avoids selling offers at the same price that they are bought)

// on any given day, process first the buys and then the sells
// buys are ordered by highest price first, then lowest
// sells are ordered by highest sell price first, then lowest
struct Event
{
    bool sell; // whether sell or buy
    int client_id;
    ll price; // sell or buy price
    int day;  // day of sell or buy
};

bool operator<(const Event &a, const Event &b)
{
    if (a.day != b.day)
        return a.day > b.day;
    if (a.price != b.price)
        return a.price > b.price;
    return a.sell > b.sell;
}

struct Client
{
    // K most profitable sell paths beggining at a client
    // in other words, if a sheet is sold to this client, how much profit can it make
    priority_queue<ll> most_profit;
};

int N, K;

vector<Event> evs;
vector<Client> clients;
umap<int, Day> days;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cin >> N >> K;
        vector<int> A(N), B(N);
        vector<ll> X(N), Y(N);

        days.clear();

        evs.clear();
        rep(i, N)
        {
            cin >> A[i] >> B[i] >> X[i] >> Y[i];
            evs.push_back(Event{
                false, // buy
                i,     // client_id
                X[i],  // buy_price
                A[i],  // buy_day
            });
            evs.push_back(Event{
                true, // sell
                i,    // client_id
                Y[i], // sell_price
                B[i], // sell_day
            });
        }
        sort(evs.begin(), evs.end());

        clients.assign(N, Client{
                              {}, // most_profit
                          });
        rep(i, N) clients[i].most_profit.push(0); // 0 profit path (terminal path)

        for (Event &ev : evs)
        {
            if (ev.sell)
            {
                // sell from day to a single client

                // extract K best offers
                Day &d = days[ev.day];
                vector<ll> most_profit;
                most_profit.reserve(K);
                while (most_profit.size() < K && !d.deals.empty())
                {
                    ll profit = d.deals.top();
                    d.deals.pop();
                    most_profit.push_back(profit);
                }
                for (ll profit : most_profit)
                    d.deals.push(profit);

                // add to client, but subtract the sell price (X - Y + Z)
                Client &c = clients[ev.client_id];
                for (ll profit : most_profit)
                    c.most_profit.push(profit - ev.price);
            }
            else
            {
                // buy from a single client to a day

                // extract K best paths
                Client &c = clients[ev.client_id];
                vector<ll> most_profit;
                most_profit.reserve(K);
                while (most_profit.size() < K && !c.most_profit.empty())
                {
                    ll profit = c.most_profit.top();
                    c.most_profit.pop();
                    most_profit.push_back(profit);
                }
                for (ll profit : most_profit)
                    c.most_profit.push(profit);

                // add these paths at the buy price of this client
                Day &d = days[ev.day];
                /*d.buyers.push_back(Buyer{
                    ev.price,    // buy_price
                    most_profit, // most_profit
                });*/
                for (ll profit : most_profit)
                    d.deals.push(ev.price + profit); // add X + Z to the deal list
            }
        }

        // take K best paths
        ll ans = 0;
        priority_queue<ll> all_best;
        for (Client &c : clients)
        {
            while (!c.most_profit.empty())
            {
                all_best.push(c.most_profit.top());
                c.most_profit.pop();
            }
        }

        rep(k, K)
        {
            if (all_best.empty())
                break;
            ans += all_best.top();
            ans %= MOD;
            all_best.pop();
        }

        cout << "Case #" << tc + 1 << ": " << ans
             << "\n";
    }
}
