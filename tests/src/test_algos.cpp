#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <memory>
#include "algos.h"
#include "cc.h"
#include "lm.h"
#include "fixtures/mtcars.h"

TEST_CASE_METHOD(MTCars, "Test LastRelimpAlgorithm.evaluate_column-1") {
	std::vector<std::string> full_x_labs = {"cyl", "disp", "hp", "drat", "qsec"};
	Model full_model = basic_lm(get_x(full_x_labs), get_y());

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);

	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};
	auto cc = ra->evaluate_column(get_x(x_labs), get_y(), 0, full_model);

	auto mean_without = cc.get_mean_without_column();
	REQUIRE_THAT(
			mean_without,
			Catch::Matchers::WithinRel(0.7099, 0.001)
	);

	auto mean_with = cc.get_mean_with_column();
	REQUIRE_THAT(
			mean_with, 
			Catch::Matchers::WithinRel(0.7903, 0.001)
	);

	auto lift = cc.get_lift();
	auto calculated_lift = mean_with - mean_without;
	REQUIRE_THAT(
			lift, 
			Catch::Matchers::WithinRel(calculated_lift, 0.001)
	);
}

TEST_CASE_METHOD(MTCars, "Test LastRelimpAlgorithm.evaluate_column-2") {
	std::vector<std::string> full_x_labs = {"qsec", "vs", "am", "gear", "cyl"};
	Model full_model = basic_lm(get_x(full_x_labs), get_y());

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);

	std::vector<std::string> x_labs = {"qsec", "vs", "am", "gear"};
	auto cc = ra->evaluate_column(get_x(x_labs), get_y(), 0, full_model);

	auto mean_without = cc.get_mean_without_column();
	REQUIRE_THAT(
			mean_without,
			Catch::Matchers::WithinRel(0.7191, 0.001)
	);

	auto mean_with = cc.get_mean_with_column();
	REQUIRE_THAT(
			mean_with, 
			Catch::Matchers::WithinRel(0.7699, 0.001)
	);

	auto lift = cc.get_lift();
	auto calculated_lift = mean_with - mean_without;
	REQUIRE_THAT(
			lift, 
			Catch::Matchers::WithinRel(calculated_lift, 0.001)
	);
}

TEST_CASE_METHOD(MTCars, "Test LastRelimpAlgorithm.evaluate_columns-1") {
	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);

	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};
	auto ccs = ra->evaluate_columns(get_x(x_labs), get_y());
	REQUIRE(ccs.size() == get_x(x_labs).n_cols);

	for (ColumnContribution cc : ccs) {
		REQUIRE(cc.get_lift() != 0);
	}
}

