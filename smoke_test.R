library("relix")

fit <- lm("mpg ~ disp + hp + drat", data = mtcars)
output <- relix(fit, "last", intercept = FALSE)
print(output)
