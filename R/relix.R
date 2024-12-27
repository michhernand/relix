#' @useDynLib relix, .registration = TRUE
#' @importFrom Rcpp evalCpp
#' @importFrom RcppArmadillo armadillo_set_seed
#' @importFrom stats model.matrix model.frame model.response

if(getRversion() >= "2.15.1") utils::globalVariables(c("_relix_relix_r"))
#'
#' .onUnload <- function(libpath) {
#' library.dynam.unload("relix", libpath)
#' }
#' Calculates Relative Importance of Linear Model Terms From Fit
#'
#' @title Calculate Relative Importance from Fit
#' @description Calc relative importance of terms in linear model (from fit)
#' @param fit Linear model produced by lm().
#' @param type String indicating which importance algorithm should be used.
#' @return Dataframe showing the relative importance of each column.
#' @examples
#' \dontrun{
#' fit <- lm(mpg ~ hp + drat, data = mtcars)
#' importances <- relix(fit, "last")
#' }
#' @export
relix <- function(fit, type) {
  model_matrix <- stats::model.matrix(fit)

  model_frame <- stats::model.frame(fit)
  model_response <- stats::model.response(model_frame)

  result <- relix_r(model_matrix, model_response, type, TRUE)

  df <- data.frame(colnames(model_matrix), result)
  colnames(df) <- c("column", "importance")
  return(df)
}

#' Calculates Relative Importance of Linear Model Terms From Data
#'
#' @name relix_r
#' @title Calculate Relative Importance from Data
#' @description Calc relative importance of terms in linear model (from data)
#' @param x Numeric matrix of predictors
#' @param y Numeric vector of response variable
#' @param type String indicating which importance algorithm should be used.
#' @param intercept Boolean indicating whether to include an intercept term.
#' @return A numeric vector of relative importance values.
#'
#' @examples
#' \dontrun{
#' x <- as.matrix(mtcars[,2:3])
#' y <- mtcars$mpg
#' relix_r(x, y, type = "first", intercept = TRUE)
#' }
#'
#' @export
relix_r
