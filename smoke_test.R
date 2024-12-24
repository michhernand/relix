#!/bin/bash
fit <- lm("mpg ~ cyl + disp + hp + drat", data = mtcars)

relix_func <- function() {
	print(relix::relix(fit, "first", intercept = TRUE))
}

relaimpo_func <- function() {
	print(relaimpo::calc.relimp(fit, type = "first"))
}

print("RELAIMPO")
relaimpo_func()
print("RELIX")
relix_func()

