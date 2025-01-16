# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-01-16

- Dropped support for Python 3.9.

- Added compatibility with NumPy 2.

## [0.2.2] - 2023-07-09

- Python GIL is now released while minilsap is running the calculation.

## [0.2.0] - 2022-02-07

- Changed API to be a drop-in replacement for
  `scipy.optimize.linear_sum_assignment`.

- Added typing information.

## [0.1.1] - 2022-02-07

Re-release with project name changed from `lsap` to `minilsap`.

## [0.1.0] - 2022-02-07

Initial release, based on the LSAP algorithm in SciPy 1.18.0.
