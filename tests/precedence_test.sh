#!/bin/bash

(echo A && echo B) || (echo C && echo D)

(echo A || echo B) && (echo C || echo D)


