fit <- lm("mpg ~ disp + hp", data = mtcars)

relix_func <- function() {
	print(relix::relix(fit, "last"))
}

print(relix_func())


