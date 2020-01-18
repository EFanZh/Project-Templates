pub fn fibonacci(n: u32) -> u32 {
    let mut a = 0;
    let mut b = 1;

    for _ in 0..n {
        let c = a + b;

        a = b;
        b = c;
    }

    a
}

#[cfg(test)]
mod tests {
    use super::fibonacci;

    #[test]
    fn test_fibonacci() {
        assert_eq!(fibonacci(0), 0);
        assert_eq!(fibonacci(1), 1);
        assert_eq!(fibonacci(2), 1);
        assert_eq!(fibonacci(3), 2);
        assert_eq!(fibonacci(4), 3);
        assert_eq!(fibonacci(5), 5);
        assert_eq!(fibonacci(6), 8);
        assert_eq!(fibonacci(7), 13);
    }
}
