// RUN: %clang_cc1 -verify -fopenmp %s

void foo();

int main(int argc, char **argv) {
  #pragma omp target
  #pragma omp teams distribute simd default // expected-error {{expected '(' after 'default'}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute simd default ( // expected-error {{expected 'none' or 'shared' in OpenMP clause 'default'}} expected-error {{expected ')'}} expected-note {{to match this '('}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute simd default () // expected-error {{expected 'none' or 'shared' in OpenMP clause 'default'}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute simd default (none // expected-error {{expected ')'}} expected-note {{to match this '('}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute simd default (shared), default(shared) // expected-error {{directive '#pragma omp teams distribute simd' cannot contain more than one 'default' clause}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute simd default (x) // expected-error {{expected 'none' or 'shared' in OpenMP clause 'default'}}
  for (int i=0; i<200; i++) foo();

  #pragma omp target
  #pragma omp teams distribute simd default(none)
  for (int i=0; i<200; i++) ++argc; // expected-error {{variable 'argc' must have explicitly specified data sharing attributes}}

  return 0;
}
