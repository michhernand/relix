# Data set is from NYC taxi rides data set
# Link: https://www.nyc.gov/site/tlc/about/tlc-trip-record-data.page

DATA_URL = "https://d37ci6vzurychx.cloudfront.net/trip-data/yellow_tripdata_2024-10.parquet"

df <- arrow::read_parquet(DATA_URL)
fit <- lm(
  total_amount ~ trip_distance + fare_amount + extra + tip_amount,
  data = df
)

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
