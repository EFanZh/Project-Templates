export function fibonacci(x: number): number {
    let a = 0;
    let b = 1;

    for (let i = 0; i < x; i++) {
        const c = a + b;

        a = b;
        b = c;
    }

    return a;
}
