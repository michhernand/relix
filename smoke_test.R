library("relix")

x <- as.matrix(mtcars)
x_ok <- is.matrix(x)
if (x_ok == FALSE) {
	stop("x is not a matrix")
}
x_ok <- is.matrix(x) && is.numeric(x)

x_ok <- is.numeric(x)
if (x_ok == FALSE) {
	stop("x is not numeric")
}

y <- mtcars[,3]
y_ok <- is.numeric(y)

if (y_ok == FALSE) {
	stop("y is not numeric")
}

print("X...")
print(x)

print("Y...")
print(y)

print("************************************************")

print(relix_r(x, y))
