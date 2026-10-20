## gcc-mcdc-tests

[![DOI](https://zenodo.org/badge/1204275360.svg)](https://doi.org/10.5281/zenodo.23287624)

Archive Link: https://doi.org/10.5281/zenodo.23287624

---

## GCC MC/DC Coverage Requirements & Testsuite

**Version:** 1.1.0
**Date:** 2026-10-10

---

1. OVERVIEW
--------------------------------------------------------------------------------
The contents in this repo, along with some external code redistributed here and
described below, provide a requirements-based C language test suite for GCC's 
MC/DC coverage capabilities.  Two test programs are executed to generate .gcov 
coverage files, which are then analyzed by a third program to verify expected 
coverage output using a suite of tests designed to perform requirements-based
verification of expected line, branch, and condition coverage reporting.  The 
tool is geared to assist in gcc mcdc tool qualification across a range of 
software usage criticalities and as well as to align with FAA standards. 

--------------------------------------------------------------------------------
2. FEATURES
--------------------------------------------------------------------------------
- C (c17, or equivalently iso9899:2017) language tests, not the gcc extensions
- Tests are designed and numbered to selectively meet requirements corresponding 
  to different criticality-of-use levels corresponding to FAA DAL-C, DAL-B, and 
  DAL-A.  The DAL-A tests include all tests in the suite. Artifacts are intended 
  to comply with DO-330 and DO-178B Tool Qualification FAA standards.  
- Doxygen-style comments are included for requirements-to-test bidirectional 
  traceability and external design documentation generation
- The included requirements set is based on an and Ada version published in 2007
  through an FAA-sponsored 'Software Verification Tools Assessment Study', 
  at the following publicly-available reference:  DOT/FAA/AR-06/54. 
- This software is released under the GNU Public License Agreement and contains
  no warranties, see below. 
- This software is summarized further by the author's youtube video: 
  https://www.youtube.com/watch?v=BnIUxWchMGM
  and in the following IEEE publication:  
  https://ieeexplore.ieee.org/document/11732044

--------------------------------------------------------------------------------
3. SYSTEM REQUIREMENTS
--------------------------------------------------------------------------------
- GCC version(s):
   - Tested with **gcc/gcov 14.3.0** on **Ubuntu 24.04.4 LTS**
   - Tested with **gcc/gcov 16.0.1** on **Ubuntu 24.04.4 LTS**
   - Other gcc/gcov versions may behave differently (see issues), please
     write issue accordingly
- Required Libraries / Dependencies:
   1) gcov-19.c - This is the testsuite that GCC uses for its releases, and 
      is available under GNU Public license from gcc's github site following 
	  this tree:  [gcc.git] / gcc / testsuite / gcc.misc-tests / gcov-19.c.
	  It is used preferentially to test requirements if a test exists, then 
	  supplemented by 'additional_gcc_testsuite.c' for comprehensive 
	  requirements-based verification testing.
   2) Mini_UT-Assert - The testrunner runs with a mini verion of NASA's Open Source
      'utassert' unit test framework, which is available here:
      https://github.com/lore-prokop/Mini_UT-Assert. The original UT-Assert
      is released under the NASA Open Source Agreement (NOSA), and is publicly
      available at https://sourceforge.net/projects/cfs-ut-assert/files/.
      Only the one testrunner program itself uses a minimal set of utassert
      function calls, so these tests could be  converted into another unit test
      framework if desired. The testrunner is linked with the following utassert
      files only:  utassert.o, ut_hooks_stubs.o

--------------------------------------------------------------------------------
4. INSTALLATION and USAGE
--------------------------------------------------------------------------------
The overall usage is as follows: 

Step 1) gcc (see versions above) compile the testsuites gcc_testsuite_gcov-19.c and 
        additional_gcc_testsuite.) with no optimization, c-17, and coverage 
		similar to the following:  
        gcc -std=c17 -Wall -Wstrict-prototypes -DUT_VERBOSE -O0 -fprofile_arcs \
		    -ftest-coverage -fcondition-coverage 
		- see makefile 'makefile-gcc-tests' and 'makefile-add-tests' 
		
Step 2) Run gcov on both testsuites above to generate '.gcov' files used as input 
        to 'gcc-mcdc-ver-tests-utassert_testrunner.c, Ex.
        gcov -abcfg additional_gcc_testsuite.c -o 
		      add_tests-additional_gcc_testsuite
		- see makefile 'makefile-gcc-tests' and 'makefile-add'tests'
		
Step 3) Compile and run the utassert testrunner. This program will analyze the 
        .gcov files produced above as input for proper coverage analysis.
		include unit test switches: -DENABLE_HOOKS_AND_STUBS -DUT_VERBOSE
   	    (see makefile 'mcdc-ver-tests-utassert_testrunner')
		
Step 4) Verify Expected Results:  The testrunner will run one overall test
        for each of the 40 requirements, each requirement test containing a 
		number of individual test cases.  The overall expected output is to 
		the terminal, seeing 421 individual test cases pass.  Details are shown
		in file 'expected_output.txt', but the overall summary should be:
		
				Tests Executed:    43
				Assert Pass Count: 486
				Assert Fail Count: 0
				
Command Line Shortcuts:   The files in this distribution contain makefiles to
perform the steps above, including generating documentation with the following 
four commands:

	$ make -f makefile-gcc-tests
	$ make -f makefile-add-tests
	$ make -f makefile-utassert-ver-tests
	$ doxygen Doxyfile_mcdc.txt
	
--------------------------------------------------------------------------------
5. FILE and DIRECTORY DESCRIPTIONS
--------------------------------------------------------------------------------
Primary contributions of this work:
* additional_gcc_testsuite.c - The tests used in addition to those provided by 
    gcc to test coverage according to requirements.
* gcc-mcdc-ver-tests-utassert_testrunner.c - The overall test runner to inspect
  each requirement against the .gcov files to provide expected results. Uses 
  output from the gcc testsuite and the additional testsuite
* requirements+trace.dox - The set of C language doxygen-style requirements 
  used for this testsuite.  Doxygen-based requirements list used to generate 
  traceability information in doxygen output. This file also contains the 
  function list and traceability information for the gcc-owned test file
  'gcc_testsuite_gcov-19.c' so that the gcc file is unmodified, yet documented
  externally for traceability
* Requirement-Mapping.pdf - pdf version of the requirements, mapping C 
  language requirements used herein to the Ada requirements published in 
  DOT/FAA/AR-06/54
* /dox/rtf/refman.rtf - contains requirement to test traceability matrix, and 
  provides external documentation of code, tests, and expected output
  (doxygen doesn't seem to let you change the name)

Other Primary files:
* gcc_testsuite_gcov-19.c - the existing gcc 14 testsuite, copied for use here,
    from [gcc.git] / gcc / testsuite / gcc.misc-tests / gcov-19.c

Other files:
* readme.txt - This file
* license.txt - The GPL License for this code
* makefile-add-tests - compiles and runs 'additional_gcc_testsuite' in Steps 1 & 2
* makefile-gcc-tests - compiles and runs 'gcc_testsuite_gcov-19.c' in Steps 1 & 2
* makefile-utassert-ver-tests - compiles and runs 
     'mcdc-ver-tests-utassert_testrunner' - utassert testrunner file in Step 3
* expected-output.txt

utassert library and related:
* Acquire utassert library from github:  lore-prokop/Mini_UT-Assert

doxygen-related files:
* rtf_extensions_file - used to add author name
* Doxyfile_mcdc.txt - config file for doxygen, only generates rtf by default, but
                    can be modified to generated whatever output is needed
* /dox/rtf - doxygen-generated rtf file (refman.rtf) is located here

--------------------------------------------------------------------------------
6. KNOWN FEATURES / CONSTRAINTS / USAGE GUIDELINES / NOTES
--------------------------------------------------------------------------------
* C Language Version -
The version of the C language standard chosen is C17, also known as 
iso9899:2017.  GCC version 14.1 by default compiles C with GCC extensions,
so the default should be changed to -std=c17.  Some of the gcc extensions effect 
syntax and conditionals, such as the ternary operator. The GCC extensions were 
not included in this test suite.

* Compiler Optimizations - 
Several requirements in AR-06-54 (C-16 through C-19) state that compiler 
optimizations should not affect tool coverage reports, but gcc's code coverage 
tools are designed to work with no optimization.  This is a known design 
characteristic and usage constraint.  Running gcc with optimizations 'on' found 
that optimizations were not counted as missing lines such as with '#####',
but they are marked as unexecuted with a '-:', so they can be 
detected.  The recommended approach is to use gcc's optimization reports 
separately, generated with ' -fopt-info-all' to understand compiler behavior 
regarding optimizations and use coverage reports with no optimization to 
assess test coverage. Also, all lines with '-:' can be inspected in coverage
output.

* Optimization of known Compile-time Constants/Values
- 'assignment to address' in conditional - Assignments to addresses are treated 
as immutable numeric literals and optimized out even without optimization,'-O0'.  
This is demonstrated in test B1.11, when assigning a pointer to an address 
inside of a conditional, 'if (ptr = &array[0]) ...'.  A decision does not 
show up in the coverage report and always evaluates to true.  Care should be 
taken within assignments because confusing '=' with the relational '==' would 
not be flagged as unexercised code in the coverage report.
- Similarly, test case C20.12 optimizes out a condition within a macro when the 
called with a numeric literal at compile time.  
- Several cases where variable values are known and immutable at compile time
are compiled out. To ensure they are not optimized out, they can be declared
'volatile'. This will ensure branching related to them appear in the coverage
report.

* Dead Code Optimizations -
When running test case C-19, it was discovered that even compiling with '-O0', 
or no optimization, some dead code was compiled out and did not show up in the 
'lines not covered' metric identified in the gcov output file with a '#####'.  
However, in this case, the 'blocks not covered' gcov metric did identify the dead 
code blocks that were not covered and the lines were marked as '-:'.    This is 
another usage condition of the gcc gcov tool when identifying dead code.   Not 
only must the optimization be zero (-O0), but both lines and blocks uncovered 
must be inspected in the gcov output.  Both the '#####' and the '%%%%%' 
designations in the gcov output must be inspected to fully identify dead code.

* Ternary Operator Numeric Literal Optimization -
For two of the ternary operator tests, B7.3, using gcc test mcdc018b, and B7.4, 
using gcc test mcdc020a, a ternary operator condition is optimized out under 
particular circumstances.  In B7.3,  equal numeric literal values are given for 
both the 'true' and the 'false' return value in the ternary operator as in 
"n = c ? 0 : 0".  When used this way, the coverage report shows no conditions 
or branches, but the line coverage is properly reported.   Similarly, in test 
B7.4, there is a specific use case when an input parameter that has been 
previously hard coded to a literal '1' is compared to '1' in a ternary, such 
as in the statement 'a ? 1: 0'.  In both of these cases, the use of literal 
numeral values triggers the compiler to eliminate the decision.  Slight changes 
to these structures such as using 'a ? 2: 0' in test B7.4 and all other 
non-trivial uses produced coverage results as expected for the c language 
ternary operator. These are considered trivial cases.

* Boolean expressions in assignments - 
Three tests for requirement B8, and one for requirement A5, are noted.   In B8, 
'Boolean expressions in assignments', the requirement calls for decision 
coverage to be shown for Boolean assignment expressions, but as stated in 
AR-06-54, "In C ... relational operators do not interpret their operands as 
boolean".    Coverage reports for test B8.6, which makes an assignment with 
relational operators ( 'a = a > a'), and test B8.7, which makes an assignment 
with the logical not '!' ('a=!b') , show no decision paths when they are 
outside of a "&&" or "||" decision, which is expected in C.  Single statements 
residing outside of condition statements that do not branch as a result of the 
assignment show only one decision path.  Test B8.5 is a specific case of an 
identity assignment within an if statement ('a = a == a'), also does not 
identify multiple decision paths in the coverage report.  Lines not taken are, 
however, identified in the output.   This  specific case is believed to be 
related to earlier compiler optimizations when comparing identity variables.  
Similarly, in test A5, when testing a coupled term inside of a relational 
operator ('a != a'), no decisions are shown, and it appears to be compiled out 
shown by the symbol '-:' rather than '#####' in the coverage report.  This is
also believed to be an example of an atomic trivial case.

* 64 Condition Maximum - 
The gcc compiler limits the number of conditions included in coverage 
statistics to 64 when compiling on a 64 bit computer, and 32 on a 32 bit 
computer.  Above 64 (or 32) conditions within a single decision, the compiler 
generates a warning '-Wcoverage-too-many-conditions'.  Test A-7 verifies 
this limit, and the behavior is as expected.  The compiler warning is 
suppressed in the gcc test suite so no warning is annunciated, but without 
that suppression via the '#pragma GCC diagnostic ignored' command, 
it was tested to be annunciated.  

* Conditional Compilation - 
Code conditionally compiled out does not contain missing line coverage marks
such as '#####'.  It is, however, marked with '-:' designating code not
executed.  To see all code not executed, '-:' should be inspected. This is
shown in test case C-23.

* Notes Assembly 'asm' and Fortran languages within C - 
GCC coverage tools ignore assembly 'asm' blocks as identified with a '-:' in 
the gcov output.  Fortran coverage may be instrumented if the Fortran code is
separately compiled with gcc coverage instrumentation.
 
--------------------------------------------------------------------------------
7. CONTRIBUTING
--------------------------------------------------------------------------------
Contributions are welcome to expand this test suite to other languages, to 
report bugs, or expand with any missing tests. Please contact author.

--------------------------------------------------------------------------------
8. LICENSE
--------------------------------------------------------------------------------
GNU GPL LICENSE
 
The 'GCC MC/DC Coverage Requirements & Testsuite', including files 
'additional_gcc_testsuite' and 'gcc-mcdc-ver-tests-utasset_testrunner' providing 
supplemental tests (above gcc) to verify gcc's mcdc capabilities against 
requirements - Copyright (C) 2026 Lorraine Prokop

This program is free software: you can redistribute it and/or modify it under the 
terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this 
program.  If not, see <https://www.gnu.org/licenses/>.  

--------------------------------------------------------------------------------
9. CONTACT
--------------------------------------------------------------------------------
Author:  Lorraine E. Prokop
Email: lore.prokop@gmail.com
