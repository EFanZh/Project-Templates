import * as assert from "assert";
import * as example from "../example";

describe("example", () => {
    describe("fibonacci", () => {
        it("is correct", () => {
            assert.equal(example.fibonacci(0), 0);
            assert.equal(example.fibonacci(1), 1);
            assert.equal(example.fibonacci(2), 1);
            assert.equal(example.fibonacci(3), 2);
            assert.equal(example.fibonacci(4), 3);
            assert.equal(example.fibonacci(5), 5);
            assert.equal(example.fibonacci(6), 8);
            assert.equal(example.fibonacci(7), 13);
        });
    });
});
