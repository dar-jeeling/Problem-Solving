type F = (x: number) => number;

function compose(functions: F[]): F {
  return function (x): number {
    return functions.reduceRight((acc, fn) => fn(acc), x);
  };
}
