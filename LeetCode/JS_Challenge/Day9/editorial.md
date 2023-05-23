## 핵심 컨셉 : Extremely important example of a higher-order function - _Memoization_

### Pure Functions

- memoization은 오직 **_pure functions_**에서만 올바르게 동작한다.
  - **pure function** : 같은 input이 들어오면 항상 같은 output을 리턴하며, side-effects를 가지지 않는 함수
  - memoization과 같은 성능 최적화를 누리기 위해, 가능한 함수를 pure function으로 만들어야 한다.

### Memoization Use-cases in Web Development

- **Caching Website Files**
  일반적으로 대형 웹사이트는 많은 JS 파일로 구성되며, 사용자가 서로 다른 페이지를 방문할 때 동적으로 다운로드 받게 됨.
  이런 상황에서 브라우저 캐싱이 중요한 역할을 한다. 🌧️ `tanstack query`와 같은 라이브러리에서 이를 이용해서 성능 최적화를 한다.

  브라우저 캐싱은 웹 브라우저가 자주 사용하는 파일을 로컬 디스크에 저장하는 기능이다. 이렇게 하면, 동일한 파일을 다시 요청할 때 서버에서 다시 다운로드 받는 것 보다 빠르게 로컬 디스크에서 로드할 수 있따.

  문제는 **파일의 내용이 변경되었을 때** 브라우저가 이를 알아채고 새로운 파일을 다운로드 받아야 한다는 것이다. 이를 위해 **파일 이름을 파일 내용의 해시로 구성하는 패턴**을 사용한다.
  **해시는 파일 내용에 따라 고유하게 생성되므로, 파일 내용이 변경되면 해시 값도 변경되고, 따라서 파일이름도 변겨오딘다.**

  예를 들어, 파일 `script.js`가 있을 때, 이 파일의 내용에 대한 해시 값이 `123abc`라면 이 파일의 이름을 `script.123abc.js`와 같이 사용한다.
  만약 파일의 이름이 변경되면 해시 값도 `456dfef`와 같이 변경되고, 파일이름도 `script.456def.js`로 변경된다.

  이러한 방법으로 cache invalidation 문제 (언제 캐시된 파일을 버리고 새로운 파일을 다운로드 받아야 할지를 결정하는 문제)를 효과적으로 해결할 수 있다.
  해시를 사용함으로써 파일 내용에 따라 자동으로 처리할 수 있다.

  예시)
  ![](https://i.imgur.com/XvhPgS2.png)

  28.ef234422c67d1198.js 파일에서 ef234422c67d1198 부분은 파일의 내용을 해시한 결과이다.

- **React Component**
  `React.memo`를 사용하여 불필요한 렌더링을 줄인다.

- **Caching API Calls**
  네트워크 요청 함수에 `key`를 사용하여, `key`에 해당하는 값을 캐싱하도록 하여 성능을 높힐 수 있다.
  그러나, 이 경우 `data staleness`에 관한 문제가 생기고 이에 대한 해결방안을 마련해야 한다.

  - a few ways to handle this
    1. 항상 값이 변경되었는지 묻는 요청을 API에 보낸다. (🌧️ `E-tag`나 `Last-Modified` 헤더를 이용한 조건부 요청을 뜻하는 듯)
    2. Websocket을 사용하여 데이터베이스의 값 변경을 구독한다.
    3. 만료 시간 값을 지정한다.

## Note

### TypeScript의 제네릭을 활용한 코드 작성하기

```typescript
type Fn = (...params: any[]) => any;

function memoize<T extends Fn>(fn: T): T {
  const map = new Map<string, ReturnType<T>>();

  return ((...args: Parameters<T>): ReturnType<T> => {
    const key = JSON.stringify(args);

    if (map.has(key)) {
      return map.get(key) as ReturnType<T>;
    }

    const result = fn(...args);
    map.set(key, result);
    return result;
  }) as T;
}
```

- `<T extends Fn>`은 TypeScript의 제네릭 타입을 정의하는 문법이다. 이는 `T`라는 타입 변수를 선언하며, 이 `T`는 `Fn` 타입 또는 그 서브 타입을 가질 수 있다.
- `Fn`은 `(...params: any[]) => any`라는 함수 타입을 나타내느다. 따라서 `<T extends Fn>`은 `T`가 이와 같은 함수 타입, 즉 어떤 수의 매개변수를 받고 어떤 타입의 값을 변환할 수 있는 함수 타입이어야 함을 의미한다.
- `memoize` 함수의 반환타입도 `T`로 지정되어 있는데, 이는 `memoize` 함수가 입력으로 받은 함수와 동일한 타입의 함수를 반환함을 의미한다. (어떤 함수르 `memoize` 함수에 넣더라도 그 함수의 타입이 보존된다.) ▶️ 아룰 통해 타입 안전성을 더욱 확보할 수 있다.
- 제네릭을 사용하면 `memoize` 함수가 입력 함수의 정확한 타입을 추적하고 그 타입을 그대로 보존할 수 있따.

### `JSON.stringify`를 사용할 때 주의점

- 순환 참조를 가진 객체나 함수 등은 문자열화할 수 없으며, 프로퍼티 순서에 따라 같은 객체도 다른 문자열로 변환될 수도 있다.
- 복잡한 상황에 대한 처리가 필요하면 key에 대한 **별도의 해시 함수**를 이용한다.

> Concerns of Professional Implementation
>
> 1. Handling Arbitrary Inputs : 함수의 입력에 따라서 문자열로 직접 변환하는 것 보다 복잡한 접근 방식이 필요할 수도 있다.
> 2. Memory Management : 다른 입력값으로 함수르 무한정 호출할 수 있으므로 메모리가 복잡해질 수도 있다. 따라서, 캐시 크기를 제한하는 매커니즘이 필요하다.
>    이러한 접근 방식으로 **Least Recently Used** Cache를 생각할 수도 있다.
>
> [이러한 내용들은 Memoize II 에서 확인한다!](https://leetcode.com/problems/memoize-ii/description/)
