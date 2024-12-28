fit <- lm("mpg ~ disp + hp + drat", data = mtcars)

relix_func <- function() {
	relix::relix(fit, "first")
}

relaimpo_func <- function() {
	relaimpo::calc.relimp(fit, "first")
}

results <- microbenchmark::microbenchmark(
	relix_func(),
	relaimpo_func(),
	times = 2000L
)
print(results)
