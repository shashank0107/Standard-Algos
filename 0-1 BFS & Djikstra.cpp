#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*** Template Begins ***/

typedef long long    ll;
typedef pair<int, int>  PII;
typedef pair<int, pair<int, int> > PIII;
typedef vector<int>  vi;

#define endl         '\n'
#define pb           push_back
#define INF          INT_MAX/10
#define F            first
#define S            second
#define mp           make_pair
#define ios          ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define hell         1000000007
#define all(a)       (a).begin(),(a).end()
#define M_PI         3.14159265358979323846264338327950288
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

// Debug //

#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

// Constants //

const int N = 1e3+7;
const int xinc[] = {-1, -1, 0, 1, 1,  1, 0,  -1};
const int yinc[] = { 0,  1, 1, 1, 0, -1, -1, -1};

/*** Template Ends ***/
int n, m, t, r1, c1, r2, c2;
char a[N][N];
int dist[N][N];


void pre(){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)	dist[i][j] = INF;
}
bool valid(int x, int y){
	return (x >= 0 && x < n && y >= 0 && y < m);
}
void nbr(int& nx, int& ny, int x, int y){
	nx = x + xinc[a[x][y]-'0'];
	ny = y + yinc[a[x][y]-'0'];
}
int djikstra(int r1, int c1, int r2, int c2){

	r1--, c1--, r2--, c2--;
	// trace4(r1, c1, r2, c2);
	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j < m; j++)	cout << a[i][j];
	// 	cout << endl;
	// }
	pre();
	dist[r1][c1] = 0;
	priority_queue<PIII, vector<PIII>, greater<PIII> > q; 
	q.push(mp(0, mp(r1, c1)));

	while(!q.empty()){
		PIII p = q.top();	q.pop();
		int di = p.F, xi = p.S.F, yi = p.S.S;
		int nx, ny;
		nbr(nx, ny, xi, yi);
		//trace6(xi, yi, di, nx, ny, a[xi][yi]);
		if (xi == r2 && yi == c2)	break;

		for(int i = 0; i < 8; i++){
			int rn = xi+xinc[i];
			int cn = yi+yinc[i];
			if (valid(rn, cn)){
				if (rn == nx && cn == ny && di < dist[rn][cn]){
					q.push(mp(di, mp(rn, cn)));
					dist[rn][cn] = di;
					//trace3(rn, cn, dist[rn][cn]);
				}
				else if (di+1 < dist[rn][cn]){
					q.push(mp(di+1, mp(rn, cn)));
					dist[rn][cn] = di+1;
					//trace3(rn, cn, dist[rn][cn]);
				}
			}
		}
	}
	return dist[r2][c2];
}

int bfs01(int r1, int c1, int r2, int c2){

	r1--, c1--, r2--, c2--;
	pre();
	deque<PIII> q;
	dist[r1][c1] = 0;
	q.push_back(mp(0, mp(r1, c1)));

	while(!q.empty()){
		PIII p = q.front();	q.pop_front();
		int di = p.F, xi = p.S.F, yi = p.S.S;
		int nx, ny;
		nbr(nx, ny, xi, yi);
		if (xi == r2 && yi == c2)	break;


		for(int i = 0; i < 8; i++){
			int rn = xi+xinc[i];
			int cn = yi+yinc[i];
			if (valid(rn, cn)){
				if (rn == nx && cn == ny && dist[rn][cn] > di){
					dist[rn][cn] = di;
					q.push_front(mp(di, mp(rn, cn)));
				}
				else if (di+1 < dist[rn][cn]){
					dist[rn][cn] = di+1;
					q.push_back(mp(di+1, mp(rn, cn)));
				}
			}
		}

	}
	return dist[r2][c2];


}

void solve(){
	
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)	cin >> a[i][j];
	cin >> t;

	for(int i = 0; i < t; i++)
	{
		cin >> r1 >> c1 >> r2 >> c2;

		cout << bfs01(r1, c1, r2, c2) << endl;
		//cout << djikstra(r1, c1, r2, c2) << endl;
	}

}

int main(){
	
	ios;
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	int t;
	//cin >> t;
	t = 1;
	while(t--)
		solve();

	return 0;
}
