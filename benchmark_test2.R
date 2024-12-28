df <- arrow::read_parquet("~/Downloads/yellow_tripdata_2024-10.parquet")
print(colnames(df))
fit <- lm("total_amount ~ trip_distance + fare_amount + extra + tip_amount", data = df)

relix_func <- function() {
	relix::relix(fit, "last")
}

relaimpo_func <- function() {
	relaimpo::calc.relimp(fit, "last")
}

results <- microbenchmark::microbenchmark(
	relix_func(),
	relaimpo_func(),
	times = 2L
)

print(results)
