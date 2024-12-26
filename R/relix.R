#' Calculates Relative Importance of Linear Model Terms
#'
#' @title Calculate Relative Importance
#' @description Calculates relative importance of terms in linear model.
#' @param fit A linear model produced by lm().
#' @param type A string indicating which importance algorithm should be used.
#' @return A dataframe showing the relative importance of each column.
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
