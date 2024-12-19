library("relix")

fit <- lm("mpg ~ disp + hp + drat + hp * drat", data=mtcars)
output <- relix(fit, "last")
print(output)

