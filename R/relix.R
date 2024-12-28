relix <- function(fit, type) {
	# independent variables
	model_matrix <- model.matrix(fit)

	# dependent variable
	model_frame <- model.frame(fit)
	model_response <- model.response(model_frame)

	result <- relix::relix_r(model_matrix, model_response, type)

	df <- data.frame(colnames(model_matrix), result)
	colnames(df) <- c("column", "importance")
	return(df)
}
