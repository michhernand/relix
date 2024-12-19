relix <- function(fit, type) {
	# independent variables
	model_matrix <- model.matrix(fit)

	# dependent variable
	model_frame <- model.frame(fit)
	model_response <- model.response(model_frame)

	result <- relix::relix_r(model_matrix, model_response)

	index_columns <- c()
	for (ix in result$index) {
		index_column <- colnames(model_matrix)[ix+1]
		index_columns <- c(index_columns, index_column)
	}

	importances <- c()
	for (importance in result$importance) {
		importances <- c(importances, importance)
	}

	if (length(index_columns) != length(importances)) {
		stop("length(index_columns) != length(importances)")
	}

	df <- data.frame(index_columns, importances)
	colnames(df) <- c("column", "importance")
	return(df)
}
