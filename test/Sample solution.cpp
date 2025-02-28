#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vpll = vector<pll>;
const ll MOD = 1000000007LL;

// Author: Andree, 27.02.2025
void solve()
{
    ll n;
    cin >> n;

    auto interact = [&](vpll v1, vpll v2)
    {
        for (auto [l, r]: v1) cout << l << "-" << r << " ";
        cout << "+ ";
        for (auto [l, r]: v2) cout << l << "-" << r << " ";
        cout << endl;
        char res;
        cin >> res;
        return res;
    };

    // first move
    ll first_sz = (n + (n > 10) * 2) / 3;
    vpll b1{{1, first_sz}}, b2{{first_sz + 1, 2 * first_sz}};
    char ch = interact(b1, b2);
    ll pirate;

    auto rcase_fin = [&](auto& rcase_fin, pll bounds, char type) -> void
    {
        ll bit1 = type == 'L';
        auto [l, r] = bounds;
        ll sz = r - l + 1;
        if (sz == 1)
        {
            ch = type;
            pirate = l;
            return;
        }

        ll qsz = (sz + 2) / 3;
        pll q1{l, l + qsz - 1}, q2{l + qsz, l + 2 * qsz - 1};
        ch = interact({q1}, {q2});
        if (ch == 'E') rcase_fin(rcase_fin, {l + 2 * qsz, r}, type);
        else
        {
            ll bit2 = ch == 'R';
            ll bit = bit1 ^ bit2;
            rcase_fin(rcase_fin, bit ? q2 : q1, type);
        }
    };

    auto rcase = [&](auto& rcase, pll bounds) -> void
    {
        auto [l, r] = bounds;
        ll sz = r - l + 1;
        if (sz == 1)
        {
            ch = interact({{1, 1}}, {{l, l}});
            pirate = l;
            return;
        }

        ll qsz = sz / 3 + (sz + 2) / 3;
        pll q{l, l + qsz - 1};
        ch = interact({{1, qsz}}, {q});
        if (ch == 'E') rcase(rcase, {l + qsz, r});
        else rcase_fin(rcase_fin, q, ch);
    };

    auto lcase = [&](auto& lcase, pll boundsl, pll boundsh) -> void
    {
        auto [l1, r1] = boundsl;
        auto [l2, r2] = boundsh;
        if (n == 3) // nice special case
        {
            ch = interact({{3, 3}}, {boundsl});
            pirate = ch == 'L' ? l1 : l2;
            return;
        }

        ll sz1 = r1 - l1 + 1, sz2 = r2 - l2 + 1;
        if (sz1 + sz2 == 1)
        {
            if (l1 == r1) ch = 'L', pirate = l1;
            else ch = 'H', pirate = l2;
            return;
        }

        ll sz = max(sz1, sz2);
        ll qsz1 = (sz + 2) / 3;
        ll qsz2 = sz / 3;
        pll light1{l1, l1 + qsz1 - 1}, light2{l1 + qsz1, l1 + qsz1 + qsz2 - 1}, light3{l1 + qsz1 + qsz2, r1};
        pll heavy1{l2, l2 + qsz1 - 1}, heavy2{l2 + qsz1, l2 + qsz1 + qsz2 - 1}, heavy3{l2 + qsz1 + qsz2, r2};
        vpll i1{light1, heavy1}, i2{light2, heavy2};
        if (qsz2 < qsz1) i2.emplace_back(2 * first_sz + 1, 2 * first_sz + 2);
        ch = interact(i1, i2);
        if (ch == 'L') lcase(lcase, light2, heavy1);
        else if (ch == 'R') lcase(lcase, light1, heavy2);
        else lcase(lcase, light3, heavy3);
    };

    if (ch == 'L') lcase(lcase, b2[0], b1[0]);
    else if (ch == 'R') lcase(lcase, b1[0], b2[0]);
    else rcase(rcase, {2 * first_sz + 1, n});

    cout << "Ninja " << pirate << " is a " + (string) (ch == 'L' ? "light" : "heavy") + " pirate" << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) solve();
}