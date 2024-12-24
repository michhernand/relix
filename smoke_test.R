#!/bin/bash
fit <- lm("mpg ~ disp + hp + drat", data = mtcars)

relix_func <- function() {
	relix::relix(fit, "first", intercept = FALSE)
}
relix_func()
