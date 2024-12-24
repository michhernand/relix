fit <- lm("mpg ~ disp + hp + drat", data = mtcars)

relix_func <- function() {
	relix::relix(fit, "first", intercept = FALSE)
}

relaimpo_func <- function() {
	relaimpo::calc.relimp(fit, "first", intercept = FALSE)
}

results <- microbenchmark::microbenchmark(
	relix_func(),
	relaimpo_func(),
	times = 2000L
)
print(results)
