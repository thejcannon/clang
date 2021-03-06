// RUN: %clang_cc1 -std=c99 -Wmissing-field-initializers -Wmissing-braces -verify %s

// Tests that using {0} in struct initialization or assignment is supported
struct foo { int x; int y; };
struct bar { struct foo a; struct foo b; };
struct A { int a; };
struct B { struct A a; };
struct C { struct B b; };

int main(void)
{
  struct foo f = { 0 }; // no-warning
  struct foo g = { 9 }; // expected-warning {{missing field 'y' initializer}}
  struct foo h = { 9, 9 }; // no-warning
  struct bar i = { 0 }; // no-warning
  struct bar j = { 0, 0 }; // expected-warning {{suggest braces around initialization of subobject}} expected-warning {{missing field 'b' initializer}}
  struct bar k = { { 9, 9 }, { 9, 9 } }; // no-warning
  struct bar l = { { 9, 9 }, { 0 } }; // no-warning
  struct bar m = { { 0 }, { 0 } }; // no-warning
  struct bar n = { { 0 }, { 9, 9 } }; // no-warning
  struct bar o = { { 9 }, { 9, 9 } }; // expected-warning {{missing field 'y' initializer}}
  struct C p = { 0 }; // no-warning
  struct C q = { 9 }; // expected-warning {{suggest braces around initialization of subobject}} expected-warning {{suggest braces around initialization of subobject}}
  f = (struct foo ) { 0 }; // no-warning
  g = (struct foo ) { 9 }; // expected-warning {{missing field 'y' initializer}}
  h = (struct foo ) { 9, 9 }; // no-warning
  i = (struct bar) { 0 }; // no-warning
  j = (struct bar) { 0, 0 }; // expected-warning {{suggest braces around initialization of subobject}} expected-warning {{missing field 'b' initializer}}
  k = (struct bar) { { 9, 9 }, { 9, 9 } }; // no-warning
  l = (struct bar) { { 9, 9 }, { 0 } }; // no-warning
  m = (struct bar) { { 0 }, { 0 } }; // no-warning
  n = (struct bar) { { 0 }, { 9, 9 } }; // no-warning
  o = (struct bar) { { 9 }, { 9, 9 } }; // expected-warning {{missing field 'y' initializer}}
  p = (struct C) { 0 }; // no-warning
  q = (struct C) { 9 }; // expected-warning {{suggest braces around initialization of subobject}} expected-warning {{suggest braces around initialization of subobject}}

  return 0;
}
