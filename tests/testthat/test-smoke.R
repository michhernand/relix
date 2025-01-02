testthat::test_that("relix runs", {
  fit <- lm(mpg ~ hp + disp, data = mtcars)
  result <- relix::relix(fit, type = "last")
  testthat::expect_equal(1, 1)
})
