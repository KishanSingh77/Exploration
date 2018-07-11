var a = [];
var io;
var ans, n, d;
io = readline().split(" ").map(function(x) { return parseInt(x)})
n = io[0]; d = io[1] * 2;
io = readline().split(" ").map(function(x) { return parseInt(x)})

a = io
ans = 0
for (var i = 0; i < n - 1; i++) {
    if (Math.abs(a[i] - a[i + 1]) > d) {
        ans += 2;
    } else if (Math.abs(a[i] - a[i + 1]) == d) {
        ans += 1 
    }
}
ans += 2;
print(ans)

