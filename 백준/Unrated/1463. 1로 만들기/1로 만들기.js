const fs = require('fs');
const stdin = fs.readFileSync('/dev/stdin').toString().trim().split('\n');

const input = (() => {
  let line = 0;
  return () => stdin[line++];
})();

// D[i] = i를 1로 만들기 위해 필요한 연산 사용 횟수의 최솟값
const n = parseInt(stdin[0]);

const dp = Array.from({ length: n + 1 }, () => 0);

dp[1] = 0;
dp[2] = 1;
dp[3] = 1;

for (let i = 4; i <= n; i++) {
  dp[i] = dp[i - 1] + 1;
  if (i % 2 === 0) dp[i] = Math.min(dp[i], dp[i / 2] + 1);
  if (i % 3 === 0) dp[i] = Math.min(dp[i], dp[i / 3] + 1);
}

console.log(dp[n]);
