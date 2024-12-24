relix <- function(fit, type, intercept = FALSE) {
	# independent variables
	model_matrix <- model.matrix(fit)
	if (intercept == FALSE) {
		model_matrix <- model_matrix[, -which(colnames(model_matrix) == "(Intercept)")]
	}

	# dependent variable
	model_frame <- model.frame(fit)
	model_response <- model.response(model_frame)

	result <- relix::relix_r(model_matrix, model_response)

	df <- data.frame(colnames(model_matrix), result)
	colnames(df) <- c("column", "importance")
	return(df)
}
