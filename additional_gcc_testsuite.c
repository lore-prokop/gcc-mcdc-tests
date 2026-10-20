/*==============================================================================
 **  GNU GPL LICENSE BANNER
 **  'additional_gcc_testsuite' - provides supplemental tests (above gcc) to 
 **  verify gcc's mcdc capabilities - Copyright (C) 2026 Lorraine Prokop
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 **===========================================================================*/

/*=========================================================================*//**
 ** \file      additional_gcc_testsuite.c
 ** \brief     Provides supplemental - in addition to gcc's testsuite - gcc/gcov
 **            mc/dc tests to verify the full set of requirements accompanying 
 **            this code. 
 ** \details   Contains Level A, B, and C coverage tests to supplement the
 **            tests already contained in the gcc open source mcdc testsuite,
 **            'gcc_testsuite_gcov-19.c'.  This program should be run with gcov 
 **            to produce .gcov output files suitable for test analysis.  
 **            Individual tests may or may not be called to demonstrate specific
 **            gcov coverage results.  The tests are duplicated in many cases to 
 **            show how calling them with different arguments changes the 
 **            coverage results.  The requirements and some tests are based on 
 **            DOT/FAA/AR-06/54, 'Software Verification Tools Assessment Study'.   
 ** \author    Lorraine Prokop 
 ** \copyright  GNU Public License
 ** \verbatim          
 ** Usage      gcc -O0 -fprofile-arcs -ftest-coverage -fcondition-coverage -Wall
 **            gcov -abcdfgH additional_gcc_testsuite.c 
 **               -o add_tests-additional_gcc_testsuite
 **            * will generate 'additional_gcc_testsuite.c.gcov' file to be used
 **              as input to 'gcc-mcdc-ver-tests-utassert_testrunner.c'
 **            * need to also compile and perform .gcov coverage against 
 **              'gcc_testsuite_gcov-19.c", available as 'gov-19.c' from
 **              [gcc.git] / gcc / testsuite / gcc.misc-tests / gcov-19.c
 **            * see makefile 'makefile-add-tests' for additional details
 ** Limitations,Assumptions,Notes:
 **            - Some tests intentionally remain uncalled to demonstrate
 **              uncovered code paths
 **            - Compiler optimization tests require specific flags (-O0 or -O3)
 **              to reproduce expected coverage behavior
 **            - Certain atomic relational and Boolean constructs do not produce
 **              decision coverage in C, as noted within the tests
 ** File_History
 **   MM/DD/YYYY  Author                DESCRIPTION
 **  ----------  --------------------- ----------------------------------------
 **   03/24/2026  Lorraine Prokop       Initial version & doc complete
 **               lore.prokop@gmail.com
 ** \endverbatim
 *//*=========================================================================*/
 
 #include <stdbool.h>
 
 #define TRUE  1
 #define FALSE 0
 
 /*==============================================================================
 ** Conditional Compile Define - used in test 23 
 **===========================================================================*/
 #define DEFINED_FOR_TEST_C23
 
 /*==============================================================================
 ** Macro Definitions for use in C-20, 21, 22 tests
 **===========================================================================*/
 
 /* Simple boolean macro */
#define IS_POSITIVE(x) ((x) > 0)

/* Macro with internal branching */
#define SAFE_DIV(a, b) ((b) == 0 ? 0 : ((a) / (b)))

/* Multi-statement macro using do/while(0) */
#define ADD_IF_EVEN(sum, x)        \
    do {                           \
        if (((x) % 2) == 0)        \
            (sum) += (x);          \
    } while (0)

/* Macro containing a conditional continue, also used in C-21 */
#define CONTINUE_IF_NEGATIVE(x)    \
    if ((x) < 0) continue

/* Macro with unreachable branch  */
#define ALWAYS_FALSE_BRANCH(x)     \
    if ((x) == 999999) {           \
        /* unreachable */          \
    } else {                       \
        (x) += 1;                  \
    }
	
#define INC_AND_CHECK(x, y)  ((x)++, (y) < 0) // used in testing comma, C-22
 
 /*==============================================================================
 ** Global Variables
 **===========================================================================*/
 int gX = 0;       /* global variable used in B_1 */

/*==============================================================================
 ** Helper Functions
 **===========================================================================*/
int inv(int a) { return (-a); }  /* inverse   */
int id(int a)  { return (a);  }  /* indentity */

/*=========================================================================*//**
 ** \brief     Statement Coverage Tests - None Covered
 ** \satisfies C-2 (partial 1/2) Statement Coverage Tests (partial)           
 ** \details   Exercises coverage of a sequence of individual statements 
 **            outside of condition statements for basic line coverage.
 *//*=========================================================================*/

int C2_2 (int a, int b, int c)
{
	a+=1;
	b+=1;
	c+=1;
	return (a + b + c);
}

/*=========================================================================*//**
 ** \brief     If-then-else statements - empty Else
 ** \satisfies C-4 (partial 10/10) If-Then-Else Tests (partial - empty else)           
 ** \details   Exercises empty else 
 *//*=========================================================================*/

int C4_1 (int a)
{
	if (a)   
	{
		return a+1;
	}
	else  // empty else
		;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - no lines covered
 ** \satisfies C-5 (partial 1/10) Switch Statement
 ** \details   Exercises coverage of a switch statement with two explicit case
 **            labels and a default branch.  The function ensures that each case
 **            label is treated as a distinct block and that the default path is
 **            recognized when no case matches.
 *//*=========================================================================*/

int C5_1(int a)  /* switch statement - no lines covered */
{
	int b = 0;
	switch (a)
	{
		case (0):
			b = 1;
			break;
		case (1):
			b = 2;
			break;
		default:
			b = -1;
	}
	return b;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - one case covered
 ** \satisfies C-5 (partial 2/10) Switch Statement 
 ** \details   Exercises coverage of a switch statement with two explicit case
 **            labels and a default branch.  The function ensures that each case
 **            label is treated as a distinct block and that the default path is
 **            recognized when no case matches.
 *//*=========================================================================*/
 
int C5_2(int a)		/* switch statement - one case covered */
{
	int b = 0;
	switch (a)
	{
		case (0):
			b = 1;
			break;
		case (1):
			b = 2;
			break;
		default:
			b = -1;
	}
	return b;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - default case covered
 ** \satisfies C-5 (partial 3/10) Switch Statement
 ** \details   Exercises coverage of a switch statement with two explicit case
 **            labels and a default branch.  The function ensures that each case
 **            label is treated as a distinct block and that the default path is
 **            recognized when no case matches.
 *//*=========================================================================*/
 
int C5_3(int a)		/* switch statement -default case covered */
{
	int b = 0;
	switch (a)
	{
		case (0):
			b = 1;
			break;
		case (1):
			b = 2;
			break;
		default:
			b = -1;
	}
	return b;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - no breaks
 ** \satisfies C-5 (partial 4/10) Switch Statement
 ** \details   Exercises coverage of a switch statement with two explicit case
 **            labels and a default branch.  The function ensures that each case
 **            label is treated as a distinct block and that the default path is
 **            recognized when no case matches.
 *//*=========================================================================*/
 
int C5_4(int a)		/* switch statement - no breaks */
{
	int b = 0;
	switch (a)
	{
		case (0):
			b = 1;
		case (1):
			b = 2;
		default:
			b = -1;
	}
	return b;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 0
 ** \satisfies C-5 (partial 5/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_5(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}
/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 1
 ** \satisfies C-5 (partial 6/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_6(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 2
 ** \satisfies C-5 (partial 7/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_7(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 3
 ** \satisfies C-5 (partial 8/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_8(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 0 -
 **            full loop
 ** \satisfies C-5 (partial 9/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_9(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}

/*=========================================================================*//**
 ** \brief     Case (switch) statement handling - Duff's Device - case 3
 **            (multi-iteration)
 ** \satisfies C-5 (partial 10/10) Switch Statement
 ** \details   Exercises coverage of a switch statement containing a while
 **            and cases used as labels within that while, 'Duff's device'.
 *//*=========================================================================*/
 
int C5_10(const int *src, int count)
{
    int sum = 0;
    int n = (count + 3) / 4;

    switch (count % 4)
    {
        do {
            case 0:
                sum += *src++;
            case 3:
                sum += *src++;
            case 2:
                sum += *src++;
            case 1:
                sum += *src++;
        } while (--n > 0);
    }
    return sum;
}


/*=========================================================================*//**
 ** \brief     Declarations generating code
 ** \satisfies C-9 Declarations generate Executable Code  
 ** \details   Exercises coverage of declarations that generate executable code.
 *//*=========================================================================*/
 
void C9_1(int b)   /*verifies that declarations that generate executable code are included in statement coverage */
{
  int i = inv(b);  /* should generate statement coverage during execution */
}

/*=========================================================================*//**
 ** \brief     Short-circuit evaluation - no impact - false    
 ** \satisfies C-10 (partial 1/2) Short-circuit evaluation impact
 ** \details   Exercises coverage behavior for logical OR expressions where the
 **            left operand may short-circuit evaluation.  Ensures that partial
 **            evaluation does not alter the number of statements reported as
 **            executed, regardless of operand values.  The following test code 
 **            was taken directly from Appendix B of AR-06-54 to verify that 
 **            partial evaluation of short-circuited expressions does not impact 
 **            statement coverage. It should be called with b=0, and b=1 with 
 **            coverage results being the same.
 *//*=========================================================================*/

void C10_1(int b, int c)   /* called with a = false */
{
  int a = b || c; 
}

/*=========================================================================*//**
 ** \brief     Short-circuit evaluation - no impact - true    
 ** \satisfies C-10 (partial 2/2) Short-circuit evaluation impact
 ** \details   Exercises coverage behavior for logical OR expressions where the
 **            left operand may short-circuit evaluation.  Ensures that partial
 **            evaluation does not alter the number of statements reported as
 **            executed, regardless of operand values.  The following test code 
 **            was taken directly from Appendix B of AR-06-54 to verify that 
 **            partial evaluation of short-circuited expressions does not impact 
 **            statement coverage. It should be called with b=0, and b=1 with 
 **            coverage results being the same.
 *//*=========================================================================*/
 
void C10_2(int b, int c)   /* called with a = true */
{
  int a = b || c; 
}

/*=========================================================================*//**
 ** \brief     Partial evaluation of ternary - no impact
 ** \satisfies C-11 Conditional expression evaluation impact
 ** \details   Exercises coverage of a ternary operator where only one branch is
 **            taken at runtime.  Verifies that the entire conditional
 **            expression is treated as a single executable line, even when only
 **            one of the possible outcomes is evaluated.
 *//*=========================================================================*/
 
int C11_1(int a)   /*verifies short circuited line for ternary operator - only one can be true at a time - is treated whole */
{
  int b = (a ? 1 : 0);  /* equiv to a = && b */ /* should show full line coverage even if only a portion is covered, a = 0  */
  return (b);
}

/*=========================================================================*//**
 ** \brief     Multi-line block handling
 ** \satisfies C-12 Multi-line block handling
 ** \details   Exercises a basic block that spans multiple physical lines.  The
 **            function verifies that once the first statement in the block is
 **            executed, all subsequent statements in the same block are treated
 **            as covered, regardless of line breaks or formatting. Adapted from 
 **            Appendix B of AR-06-54. C.3.1.1
 *//*=========================================================================*/
 
void C12_1(void)   /*verifies basic block spanning multiple lines is handled correctly */
{
  int a = 0; 
  int b = 0;
  a = a + 1;       /* if the first assignment is reached, all should be reached */
  inv(a);
  b = a > 1 ||
      a < 1;
}

/*=========================================================================*//**
 ** \brief     Single-line block handling
 ** \satisfies C-13 Single-line block handling
 ** \details   Exercises a basic block containing multiple statements placed on
 **            a single physical line.  Verifies that coverage tools do not rely
 **            on line breaks to determine block boundaries and correctly count
 **            all statements within the block.  Adapted from Appendix B of 
 **            AR-06-54. C.3.1.1
 *//*=========================================================================*/
 
void C13_1(void)   /*verifies basic block spanning a single line is handled correctly */
{                  /* verify no dependencies on the presence of line breaks */
  int a = 0;
  int b = 0;
  a = a + 1;  inv(a); b = a > 1 || a < 1;
}

/*=========================================================================*//**
 ** \brief     Multiple blocks on one line
 ** \satisfies C-14 Multiple blocks on one line
 ** \details   Exercises a control-flow construct in which both the true and
 **            false branches of an if/else statement appear on a single line.
 **            Verifies that the coverage engine correctly identifies each
 **            branch as a separate block despite compressed formatting.
 **            Adapted from Appendix B of AR-06-54. C.3.1.1
 *//*=========================================================================*/
 
int C14_1(int a)       /*verifies multiple blocks on one line are handled correctly  */
{
  if (a) inv(a); else id(a); 
  return a;
}

/*=========================================================================*//**
 ** \brief     Indentation-independent coverage
 ** \satisfies C-15 Indentation-independent coverage
 ** \details   Exercises coverage behavior across differently indented but
 **            semantically identical control-flow constructs.  Verifies that
 **            indentation and whitespace do not influence block recognition or
 **            statement coverage results. Adapted from Appendix B of AR-06-54. 
 **            C.3.1.1
 *//*=========================================================================*/
 
void C15_1(void)   /*source code indentation does not affect coverage  */
{
  int i = 1;
  while (i > 2) {   /* note, if this was i > i, it optimized it out (atomic identity optimization) */
i = i-1;            /* not executed */
  }
		if (i > 2) 
	{
		i = i-1;  /* not executed, different indent */
	}
}

/*==============================================================================
 ** Optimization Tests
 ** Note the requirements document suggests that compiler optimization should
 ** have no effect on coverage, but the design and intended usage for gcc 
 ** coverage tools is to use with -O0, no optimization, so that is gcc a usage 
 ** condition. In the cases of compiler optimization, the coverage report does 
 ** not show missing lines as '#####', but DOES show statements not executed with 
 ** '-:', so there is a distinguishing characteristic.  The recommended approach 
 ** to understand optimization is to use other gcc tools for separate 
 ** optimization reports, generated with '-fopt-info-all'.   For -O0 there was
 ** an effect, however, in some cases, each noted individually.
 ** The intent of gcc is to use other tools
 ** -O0 there was an effect, each noted individually
 ** For the "missing lines" cases with "O3" used and not called, this shows no
 ** lines missing coverage, but the iff statement in the verification document 
 ** says both assignments are marked reached 'iff' the first assignment 
 ** is reached, so it does pass this case. 
 **===========================================================================*/

/*=========================================================================*//**
 ** \brief     Killed assignment optimization impact - max optimizataion
 ** \satisfies C-16 (partial 1/2) Killed assignment optimization impact
 ** \details   Exercises coverage behavior under maximum compiler optimization.
 **            The first assignment is optimized out by GCC at -O3, it is not 
 **            reflected as a missing line with '#####' in the coverage report
 **            but is reflected as unexecuted '-:'.  For this case, using 'O3' 
 **            and not called, this shows no lines missing coverage, but the iff 
 **            statement in the verification document says both assignments are 
 **            marked reached 'iff' the first assignment is reached, so it does 
 **            pass this case. 
 *//*=========================================================================*/
 
 /// \cond
 __attribute__((optimize("O3")))
 /// \endcond
void  C16_1(void)  /* maximum optimization of GCC WILL effect coverage */
{
	int a;
	a = 12;  /* this will be optimized out and only be reflected in coverage with '-:' */
	a = 14;
}

/*=========================================================================*//**
 ** \brief     Killed assignment optimization impact - no optimization
 ** \satisfies C-16 (partial 2/2) Killed assignment optimization impact
 ** \details   Exercises coverage behavior when compiler optimization is
 **            disabled.  Both assignments remain present in the generated code,
 **            allowing the coverage engine to confirm that unoptimized builds
 **            correctly report execution of all statements.
 *//*=========================================================================*/

/// \cond
__attribute__((optimize("O0")))
/// \endcond
void  C16_2(void)  /* no optimization WILL NOT effect coverage */
{
	int a;
	a = 12;  /* this should not be optimized out and should show up in coverage report */
	a = 14;
}

/*=========================================================================*//**
 ** \brief     Common subexpression optimization impact - optimization
 ** \satisfies C-17 (partial 1/2) Common subexpression optimization impact
 ** \details   Exercises coverage behavior when a loop body is optimized out due
 **            to unreachable iteration conditions.  Under -O3, the increment
 **            operation inside the loop may be removed, allowing coverage tools
 **            to demonstrate the effect of aggressive optimization on statement
 **            visibility.
 *//*=========================================================================*/
 
 /// \cond
 __attribute__((optimize("O3")))
 /// \endcond
void  C17_1(void)  /* maximum optimization of GCC WILL effect coverage*/
{
	int a = 0;
	int j = 0;
	a = a + 1;
	for (j = 0; j<j; j++)  /* since j is never expected to run, a=a+1 should be optimized out, and shown in coverage, but does not */
	{
		a = a + 1;
	}
}

/*=========================================================================*//**
 ** \brief     Common subexpression optimization impact - no optimization
 ** \satisfies C-17 (partial 2/2) Common subexpression optimization impact
 ** \details   Exercises the same unreachable-loop construct as C17_1 but with
 **            optimization disabled.  This verifies that the increment
 **            operation inside the loop remains visible to the coverage engine
 **            even when the loop never executes.
 *//*=========================================================================*/
 
 /// \cond
 __attribute__((optimize("O0")))
 /// \endcond
void  C17_2(void)  /* no optimization WILL NOT effect coverage */
{
	int a = 0;
	int j = 0;
	a = a + 1;
	for (j = 0; j<j; j++)  /* j is never expected to run, a=a+1 would be optimized out, but shouldn't be */
	{
		a = a + 1;
	}
}

/*=========================================================================*//**
 ** \brief     Loop invariant optimization impact - optimization, 1 call
 ** \satisfies C-18(partial 1/4) Loop invariant optimization impact
 ** \details   Exercises coverage behavior when a loop is executed exactly once
 **            under optimized conditions.  The assignment inside the loop is
 **            expected to be preserved, allowing coverage tools to confirm that
 **            invariant computations are not incorrectly removed.
 *//*=========================================================================*/
 
 /// \cond
 __attribute__((optimize("O3")))
 /// \endcond
int  C18_1(int j)  /*  optimization SHOULD effect coverage */
{
	int i;
	int k;
	for (i=0; i<=j; i++)  /* called with j = 0, should return 1 and report should reflect k=1 covered */
	{
		k = 1;
	}
	j = k;
	return (k);
}

/*=========================================================================*//**
 ** \brief     Loop invariant optimization impact - optimization, 0 call
 ** \satisfies C-18 (partial 2/4) Loop invariant optimization impact
 ** \details   Exercises a loop that should not execute when called with a
 **            negative bound.  Under optimization, the assignment inside the
 **            loop may be removed entirely, demonstrating how optimization can
 **            obscure expected uncovered statements in the coverage report.
 *//*=========================================================================*/

/// \cond
__attribute__((optimize("O3"))) 
/// \endcond
int C18_2(int j)  /*  optimization SHOULD effect coverage */
{
	int i;
	int k;
	for (i=0; i<=j; i++)  /* called with j = -1, should show k not covered, if not optimized out (but is)*/
	{
		k = 1;
	}
	j = k;
	return (k);
}

/*=========================================================================*//**
 ** \brief     Loop invariant optimization impact - no optimization, 1 call
 ** \satisfies C-18 (partial 3/4) Loop invariant optimization impact
 ** \details   Exercises a loop that executes once with optimization disabled.
 **            The assignment inside the loop should appear as covered,
 **            verifying that unoptimized builds preserve all loop body
 **            statements for coverage analysis.
 *//*=========================================================================*/
/// \cond
__attribute__((optimize("O0")))
/// \endcond
int  C18_3(int j)  /*  no optimization SHOULD NOT affect coverage */
{
	int i;
	int k;
	for (i=0; i<=j; i++)  /* called with j = 0, report should reflect k=1 covered */
	{
		k = 1;           /* should show covered */
	}
	j = k;
	return k;
}

/*=========================================================================*//**
 ** \brief     Loop invariant optimization impact - no optimization, 0 call
 ** \satisfies C-18 (partial 4/4) Loop invariant optimization impact
 ** \details   Exercises a loop that does not execute when called with a
 **            negative bound under no optimization.  The assignment inside the
 **            loop should appear as not covered, verifying that coverage tools
 **            correctly report unreachable loop bodies.
 *//*=========================================================================*/
 
/// \cond
__attribute__((optimize("O0"))) 
/// \endcond
int C18_4(int j)   /* no optimization SHOULD NOT effect coverage */
{
	int i;
	int k;
	for (i=0; i<=j; i++)  /* called with j = -1, should return 0 and report should reflect k=1 not covered */
	{
		k = 1;           /* should show not covered */
	}
	j = k;
	return k;
}

/*=========================================================================*//**
 ** \brief     Dead code elimination impact - optimization
 ** \satisfies C-19 (partial 1/2) Dead code elimination impact
 ** \details   Exercises coverage behavior when the compiler removes unreachable
 **            code under optimization.  The false branch of the if-statement is
 **            optimized out at -O3, demonstrating that eliminated dead code
 **            does not appear in the coverage report except as '-:'.  
 ** \verbatim  Limitations,Assumptions,Notes:
 **            When running test case C-19, it was discovered that even 
 **            compiling with '-O0', or no optimization, some dead code was 
 **            compiled out and did not show up in the 'lines not covered' 
 **            metric identified in the gcov output file with a '#####'.  
 **            However, in this case, the 'blocks not covered' gcov metric did 
 **            identify the dead code blocks that were not covered and the lines 
 **            were marked as '-:'.    This is another usage condition of the gcc 
 **            gcov tool when identifying dead code.   Not only must the 
 **            optimization be zero (-O0), but both lines and blocks uncovered 
 **            must be inspected in the gcov output.  Both the '#####' and the 
 **            '%%%%%' designations in the gcov output must be inspected to fully 
 **            identify dead code.
 ** \endverbatim
 *//*=========================================================================*/

/// \cond 
__attribute__((optimize("O3"))) 
/// \endcond
void C19_1(void)  /* dead code optimization of GCC WILL effect coverage*/
{
	int a = 0;
    if (1)
	{
		a = 1;
	}
	else
	{
		a = 0;   /* this should be optimized out */
	}
}

/*=========================================================================*//**
 ** \brief     Dead code elimination impact - no optimization
 ** \satisfies C-19 (partial 2/2) Dead code elimination impact
 ** \details   Exercises coverage behavior when optimization is disabled.  The
 **            false branch of the if-statement remains present in the compiled
 **            output, allowing coverage tools to distinguish between line
 **            coverage and block coverage behavior for dead code constructs.
 *//*=========================================================================*/

/// \cond 
__attribute__((optimize("O0"))) 
///\endcond
void C19_2(void)  /* having no optimization for dead code WILL NOT effect coverage */
{
	int a = 0;
    if (1)
	{
		a = 1;
	}
	else
	{
		a = 2;   
		/* this should NOT be optimized out if using -O0, but IS for line coverage and IS NOT for block coverage  */
		/* though is indicated as optimized out by '-:' symbol  in output */
	}
}

/*=========================================================================*//**
 ** \brief     Tests various macro definitions
 ** \satisfies C-20 (partial 4-12/12) Macros and Inlining
 ** \details   Uses Macros with conditionals to verify that macro inlining
 **            shows up in coverage report properly.
 *//*=========================================================================*/

void C20_1(void)  /* macros - defined at top of file */
{
    int v1 = 0;
	int x4 = 4;

    /* --- IS_POSITIVE(x) macro test --- */
    int x1 = -5;
    int x2 = 10;

    if (IS_POSITIVE(x1))
        v1 = 1;
    else
        v1 = 2;

    if (IS_POSITIVE(x2))
        v1 += 10;
    else
        v1 += 20;

    /* --- SAFE_DIV(a, b) macro test --- */
    int a = 20;
    int b1 = 0;
    int b2 = 4;

    v1 = SAFE_DIV(a, b1);   /* should take b==0 branch */
    v1 += SAFE_DIV(a, b2);  /* should take normal division branch */


    /* --- ADD_IF_EVEN(sum, x) macro test --- */
    int sum = 0;
    ADD_IF_EVEN(sum, 3);    /* Compile Time Constant Optimzed out at -O0 ->branch false */
    ADD_IF_EVEN(sum, x4);    /* even → branch true, not optimized out since x is a variable */
    v1 = sum;

    /* --- CONTINUE_IF_NEGATIVE(x)  macro test --- */
    int arr[4] = { 5, -1, 7, -3 };
    int total = 0;

    for (int i = 0; i < 4; i++)
    {
        CONTINUE_IF_NEGATIVE(arr[i]);  /* continue taken twice */
        total += arr[i];
    }
    v1 = total;

    /* --- ALWAYS_FALSE_BRANCH(x) macro test --- */
    int z = 10;
    ALWAYS_FALSE_BRANCH(z);  /* true branch unreachable */
    v1 = z;
}

/*=========================================================================*//**
 ** \brief     Continue statement verification tests
 ** \satisfies C-21 continue statement
 ** \details   Exercises the continue statement in multiple ways to verify
 **            correct coverage reporting
 *//*=========================================================================*/
 
void C21_1(void)  
{
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    int v5 = 0, v6 = 0, v7 = 0, v8 = 0;
	
    /* --  Continue in a simple for loop   ------ */
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
            continue;   /* simple continue */
        v1 += i;
    }
	
    /* --------------- Continue in a while loop  ------- */
    int i2 = 0;
    while (i2 < 5)
    {
        if (i2 == 3)
        {
            i2++;
            continue;   /* continue jumps to while condition */
        }
        v2 += i2;
        i2++;
    }
    /* ----  Continue in a do-while loop  ---------------- */
    int i3 = 0;
    do {
        if (i3 == 1)
        {
            i3++;
            continue;   /* continue jumps to bottom of loop */
        }
        v3 += i3;
        i3++;
    } while (i3 < 4);
	
    /* ----   Continue in nested loops (inner loop only)  ---- */
    for (int a = 0; a < 3; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            if (b == 1)
                continue;   /* only skips inner loop */
            v4 += (a * 10 + b);
        }
    }
    /* ---  Continue with multi-condition MC/DC  -------------- */
    int a = 1, b = 0, c = 1;
    for (int k = 0; k < 4; k++)
    {
        if (a && b)          /* MC/DC: a toggled, b toggled */
            continue;
        v5 += k;
        b = !b;              /* toggle b to exercise both sides */
    }
    /* --  Continue + break interaction   -------------- */
    for (int m = 0; m < 6; m++)
    {
        if (m == 1)
            continue;       /* continue path */
        if (m == 4)
            break;          /* break path */
        v6 += m;
    }
    /* ----  Continue inside a switch     ------ */
    for (int s = 0; s < 5; s++)
    {
        switch (s)
        {
            case 1:
                continue;   /* continue from inside switch */
            case 3:
                break;      /* break only exits switch */
            default:
                v7 += s;
        }
    }
    /* --   Continue inside a macro     ------- */
    int arr[4] = { 5, -2, 7, -9 };
    for (int z = 0; z < 4; z++)
    {
        CONTINUE_IF_NEGATIVE(arr[z]);   /* macro-embedded continue */
        v8 += arr[z];
    }
}

/*=========================================================================*//**
 ** \brief     Comma operator verification tests
 ** \satisfies C-22 Comma Operator 
 ** \details   Exercises the comma operator in multiple ways to verify
 **            correct coverage reporting
 *//*=========================================================================*/
 
void C22_1(void)
{
    int v1 = 0;

    /* ---- Comma in a simple expression ---- */
    int a = 0;
    v1 = (a = 1, a + 5);

    /* ---- Comma inside an if-condition ---- */
    int b = 0;
    if ((b = 2, b > 1))
        v1 = 10;
    else
        v1 = 20;

    /* ---- Comma inside a for-loop header ---- */
    int c = 0, d = 0;
    for (int i = 0, j = 3; (i < 3, j > 0); i++, j--)
        v1 += i + j;

    /* ---- Comma inside a macro ---- */
    int x = 0, y = -1;
    if (INC_AND_CHECK(x, y))
        v1 = 1;
    else
        v1 = 2;

    /* ---- Comma where left operand has a ternary branch ---- */
    volatile int e = 0, f = 2;
    v1 = ((f == 2 ? 1 : (e+2)), f + 10);

    /* ---- Comma where right operand has a ternary branch ---- */
    int g = 3;
    v1 = (0, (g == 3 ? 100 : 200));

    /* ---- Comma inside a return-like expression ---- */
    volatile int h = 0;
    v1 = (h++, h == 1 ? 7 : 9);

    /* ---- Comma with unreachable left operand ---- */
    volatile int z = 5;
    v1 = (((z-5) && (z = 99)), z + 1);
}

/*=========================================================================*//**
 ** \brief     conditional compilation verification tests
 ** \satisfies C-23 conditional compilation
 ** \details   Uses #ifdef to conditioally compile code to verify expected 
 **            coverage reporting.  When code is compiled out conditionally, 
 **            it does NOT show up in the coverage report as missed lines with
 **            a '#####' identifier.  It does show up in the code as '-:' 
 **            though, so it can be detected as not executed.
 *//*=========================================================================*/
 
int C23_1(int b)
{
  volatile int a = 0;
#ifdef DEFINED_FOR_TEST_C23   // defined at top of file, one branch executes
	if (b)
		a = 10;
	else
		a = 11;           // this line marked as uncovered with '#####'
	
#else                     // the else part of the code is NOT compiled and does 
                          // NOT show up as missing lines with '#####' in the 
						  // coverage report. It does show up as '-:'
						  // unexecuted lines though
		a = 13;
	else
		a = 14;
#endif
  return a;
}

/*=========================================================================*//**
 ** \brief     Boolean variable handling - assorted references
 ** \satisfies B-1 Boolean variable handling
 ** \details   Exercises coverage of Boolean conditions derived from local
 **            variables, global variables, array elements, structure members,
 **            and pointers.  The function verifies that coverage tools correctly
 **            identify each Boolean reference as a separate decision point and
 **            report partial coverage when only a subset of conditions is
 **            exercised.
 *//*=========================================================================*/

void B1_1(void)   /* Boolean variable references (local variable, global variable, parameter, array object, struct object) */
{
  int i = 0;  /* local variable */
  
  gX = 0;     /* global variable */
  
  typedef struct  {  /* structure type */
	int j;
  } struct_type;
  
  int is_array[2] = {0}; /* array */
  struct_type is_array_of_struct[2] = {{0}, {0}};  // issue 1 uninitialized warning corrected;

  struct_type is_a_struct = {1};
  struct_type *is_a_struct_ptr = 0; /* pointer */
  struct_type *is_a_struct_ptr2 = &is_array_of_struct[0];
 
  /* this should show 22 branches, half not covered since only called once*/
  /* however, the last test below does NOT show a branch and is noted in limitations */
  /* The coverage results show 10/20 branches taken, and ignores the last assignment */
  /* as a decision */
  
  if (i)     
	gX = 1;
  if (gX) 
	gX = 2;
  if (is_array[0])
	gX = 3;
  if (is_array_of_struct[0].j)
	gX = 4;
  if (is_a_struct_ptr)
	gX = 5;
  if (is_a_struct.j)
	gX = 6;
  if (is_a_struct_ptr2->j)  
	gX = 7;
	
  // several 'assignment inside of boolean if' tests here, most show branches not taken, one does not!!!
  
  if (i = inv(i))    // assignment inside of boolean, from a function call DOES show branch
	gX = 8;
  if (i = 0)        // assignment inside of if, this always evaluates to zero and DOES show a branch not covered
	gX = 9;     
  if (i = is_a_struct_ptr2->j)    // this DOES show branching in coverage
	gX = 10;    
  if (is_a_struct_ptr2 = &is_array_of_struct[0]) // assignment in boolean - NO BRANCHING SHOWN in COVERAGE FOR THIS -- SEE Notes
	// the compiler sees the above as immutable and always true at compile time, so substitutes the address literal, even with -O0
    gX = 11;
  else   
	gX=12;  /* this else statement is compiled out, and shows up in coverage as '-:' */
}

/*=========================================================================*//**
 ** \brief     Boolean variable handling - function return
 ** \satisfies B-2 Boolean variable handling
 ** \details   Exercises coverage of Boolean conditions derived from local
 **            variables, global variables, array elements, structure members,
 **            and pointers.  The function verifies that coverage tools correctly
 **            identify each Boolean reference as a separate decision point and
 **            report partial coverage when only a subset of conditions is
 **            exercised.
 *//*=========================================================================*/

int B2_1(int a)
{
	int r = 0;
	if (id(a))
	{
		r = TRUE;
	}
	if (inv(a))
	{
		r = FALSE;
	}
	return (r);
}

/*=========================================================================*//**
 ** \brief     Constant Boolean handling - constant Boolean variable
 ** \satisfies B-3 Constant Boolean handling
 ** \details   Exercises coverage behavior when conditions depend on compile-time
 **            constant Boolean values.  The function verifies that branches
 **            guarded by constant true or constant false expressions are
 **            represented correctly in the coverage report.
 *//*=========================================================================*/
 
int B3_1(void)
{
	const int a = TRUE;
	const int b = FALSE;
	int r = FALSE;
	
	if (a)
	{
		r = TRUE;
	}
	if (b)
	{
		r = FALSE;
	}
	return (r);
}

/*=========================================================================*//**
 ** \brief     Unary NOT handling - multi-variable
 ** \satisfies B-4 (partial 1/3) Unary NOT handling
 ** \satisfies A-1 (partial 3/27) Uncoupled logical operators - not
 ** \details   Exercises coverage of a multi-variable Boolean expression wrapped
 **            in a unary NOT operator.  The function verifies that coverage
 **            tools correctly interpret negated compound expressions and record
 **            execution of both the true and false outcomes.
 *//*=========================================================================*/
 
int B4_3(void)   /* multi-variable not operator */
{
	const int a = TRUE;
	const int b = FALSE;
	int r = FALSE;
	
	if (!(a || b))
	{
		r = TRUE;
	}
	else
	{
		r = FALSE;
	}
	return (r);
}

/*=========================================================================*//**
 ** \brief     Relational operator handling
 ** \satisfies B-6 Relational operator handling
 ** \satisfies A-2 Uncoupled Boolean conditions - relational
 ** \details   Exercises coverage of all standard relational operators by
 **            evaluating equality, inequality, ordering, and boundary
 **            comparisons.  Each relational test forms a separate decision,
 **            allowing the coverage engine to confirm that all relational
 **            branches are represented.
 *//*=========================================================================*/

int B6_1(int a, int b)   /* relational operators */
{
	int r = 0;
	
	if (a == b)
		r = 1;
	if (a != b)
		r = 2;
	if (a > b)
		r = 3;
	if (a < b)
		r = 4;
	if (a <= b)
		r = 5;
	if (a >= b)
		r = 6;
	
	return r;
}

/*=========================================================================*//**
 ** \brief     Boolean expressions in assignments  
 ** \satisfies B-8 Boolean assignment handling
 ** \details   Exercises coverage of Boolean and relational expressions used
 **            directly within assignment statements.  The function includes
 **            relational identities, non-identities, logical operators, and
 **            negations to verify which expressions generate decision coverage
 **            and which are treated as simple assignments. 
 ** \verbatim   Limitations,Assumptions,Notes:
 **   Three tests for requirement B8, and one for requirement A5, are noted.   
 **   In B8, the requirement calls for decision coverage to be shown for 
 **   Boolean assignment expressions, but as stated in AR-06-54, "In C ... 
 **   relational operators do not interpret their operands as Boolean".    
 *    Coverage reports for test B8.6, which makes an assignment with relational 
 **   operators ( 'a = a > a'), and test B8.7, which makes an assignment with 
 **   the logical not '!' ('a=!b') , show no decision paths when they are 
 **   outside of a '&&' or '||' decision, which is expected in C.  Single 
 **   statements residing outside of condition statements that do not branch as 
 **   a result of the assignment show only one decision path.  Test B8.5 is a 
 **   specific case of an identity assignment within an if statement 
 **   ('a = a == a'), that also does not identify multiple decision paths in 
 **   the coverage report.  Lines not taken are, however, identified in the 
 **   output.   This  specific case is believed to be related to earlier 
 **   compiler optimizations when comparing identity variables.  Similarly, 
 **   in test A5, when testing a coupled term inside of a relational operator 
 **   ('a != a'), no decisions are shown, and it appears to be compiled out shown
 **   by the symbol ':-' rather than '#####' in the coverage report.
 ** \endverbatim
 *//*=========================================================================*/
 
int B8_1(int a)   /* Boolean/relational expressions in assignment statements */
{
	int b = 0;
	if (a = (a == a))  /* relational identity in assignment statement does NOT show decisions, noted in limitations */
	{
		b = 0;
	}
	else
	{
		b = 1;
	}

	if (a = (a > a))  /* relational non-identity in assignment statement does show decisions */
	{
		b = 0;
	}
	else
	{
		b = 1;
	}
	a = (a == a);  /* relational operators in assignment statements, decisions not shown, noted in limitations */
	a = (a < a);
	a = (a > a);
	a = (a >= a);
	a = (a <= a);
	a = (a != a);
	
	a = (a && a);  /* logical operators in assignment statements */
	a = (a || a);
	a = !b;        /* atomic inverse does NOT show decisions, noted in limitations */
	a = !(a || b);
	
	return (a = (b || a));
}

/*=========================================================================*//**
 ** \brief     Implicit return handling - normal return
 ** \satisfies B-11 (partial 1/2) Implicit return handling
 ** \details   Exercises coverage behavior when a function may exit through an
 **            explicit return or through an implicit fall-through return at the
 **            end of the function.  Verifies that both return paths are
 **            represented in the coverage model. Test adapted from 
 **            DOT/FAA/AR-06/54, B.5.2.2
 *//*=========================================================================*/

int B11_1(int a)   /* implicit return -   */
{
	int r = a; /* return value */
	if (r > 0)
	{
		r = a;
		return (r);
	}
	/* implicit return here if r <= 0 */
}

/*=========================================================================*//**
 ** \brief     Implicit return handling - implicit return
 ** \satisfies B-11 (partial 2/2) Implicit return handling
 ** \details   Provides a second instance of a function with both explicit and
 **            implicit return paths.  Ensures that coverage tools consistently
 **            identify fall-through returns as executable endpoints. Test 
 **            adapted from DOT/FAA/AR-06/54, B.5.2.2
 *//*=========================================================================*/

int B11_2(int a)   /* implicit return */
{
	int r = a; /* return value */
	if (r > 0)
	{
		r = a;
		return (r);
	}
	/* implicit return here if r <= 0 */
}

/*=========================================================================*//**
 ** \brief     Uncoupled relational operators
 ** \satisfies A-2 (partial 1/27) Uncoupled relational operators
 ** \details   Exercises coverage of relational operators used independently in
 **            separate decision points.  The function verifies that each
 **            relational comparison is treated as an uncoupled condition and
 **            that coverage tools record each decision individually.
 *//*=========================================================================*/

int A2_1(int a, int b)   /* relational operators */
{
	int r = 0;
	
	if (a == b)
		r = 1;
	if (a != b)
		r = 2;
	if (a > b)
		r = 3;
	if (a < b)
		r = 4;
	if (a <= b)
		r = 5;
	if (a >= b)
		r = 6;
	
	return r;
}

/*=========================================================================*//**
 ** \brief     Coupled logical operators - xor 2 variable, all covered
 ** \satisfies A-4 (partial 1/3) Coupled logical operators
 ** \details   Exercises a coupled Boolean expression implementing XOR using
 **            AND, OR, and NOT operators.  The function verifies that coverage
 **            tools correctly track the combined evaluation of multiple Boolean
 **            operators within a single decision.  This test was Adapted from 
 **            AR-06-54 A.1.2.2.1 Example 1 "Xor2" (Ada)
 *//*=========================================================================*/

void A4_1(bool A, bool B) 
{
	int a = 0;
    // Implements A xor B using AND, OR, NOT, adapted AR-06-54 
    if ((A && !B) || (!A && B)) {
        a = 11;   // Progress.Checkpoint(11)
    } else {
        a = 12;   // Progress.Checkpoint(12)
    }
}

/*=========================================================================*//**
 ** \brief     Coupled logical operators - majority 3 variable, all covered
 ** \satisfies A-4 (partial 2/3) Coupled logical operators
 ** \details   Exercises a three-input majority voter implemented using coupled
 **            AND and OR expressions.  Verifies that coverage tools correctly
 **            represent multi-term coupled Boolean conditions.  This test was
 **            adapted from AR-06-54 A.1.2.2.1 Example 2 "Majority3" (Ada)
 *//*=========================================================================*/

void A4_2(bool A, bool B, bool C) /* This test is Adapted from AR-06-54 A.1.2.2.1 Example 2 "Majority3" (Ada)  */
{
	int a;
    // Implements 3-input majority voter using AND and OR
    if ((A && B) || (B && C) || (C && A)) {
        a = 11;   // Progress.Checkpoint(11)
    } else {
        a = 12;   // Progress.Checkpoint(12)
    }
}

/*=========================================================================*//**
 ** \brief     Coupled relational operators
 ** \satisfies A-5 Coupled relational operators
 ** \details   Exercises relational operators combined with logical operators in
 **            increasingly complex coupled expressions.  The function verifies
 **            that coverage tools correctly track relational comparisons when
 **            nested within logical constructs and when variables are reused or
 **            coupled across conditions.
 ** \verbatim   Limitations,Assumptions,Notes:
 **   Three tests for requirement B8, and one for requirement A5, are noted.   
 **   In B8, the requirement calls for decision coverage to be shown for 
 **   Boolean assignment expressions, but as stated in AR-06-54, "In C ... 
 **   relational operators do not interpret their operands as Boolean".    
 *    Coverage reports for test B8.6, which makes an assignment with relational 
 **   operators ( 'a = a > a'), and test B8.7, which makes an assignment with 
 **   the logical not '!' ('a=!b') , show no decision paths when they are 
 **   outside of a "&&" or "||" decision, which is expected in C.  Single 
 **   statements residing outside of condition statements that do not branch as 
 **   a result of the assignment show only one decision path.  Test B8.5 is a 
 **   specific case of an identity assignment within an if statement 
 **   ('a = a == a'), that also does not identify multiple decision paths in 
 **   the coverage report.  Lines not taken are, however, identified in the 
 **   output.   This  specific case is believed to be related to earlier 
 **   compiler optimizations when comparing identity variables.  Similarly, 
 **   in test A5, when testing a coupled term inside of a relational operator 
 **   ('a != a'), no decisions are shown, and it appears to be compiled out shown
 **   by the symbol ':-' rather than '#####' in the coverage report.
 ** \endverbatim
 *//*=========================================================================*/

int A5_1(int a, int b, int c)   /* coupled expressions - relational operators */
{
	int r = 0;

	// one variable coupled, shows no decisions for relational operators only in C, line coverage is correct
	if (a == a)  
		r = 1;
	if (a != a) 
		r = 2;
	if (a > a)
		r = 3;
	if (a < a)
		r = 4;
	if (a <= a)
		r = 5;
	if (a >= a)
		r = 6;
	
	// two variables, one coupled, recognizes all paths, short circuits first 'a' evaluating right to left
	if (a == (a && b))  
		r = 1;
	if (a != (a && b)) 
		r = 2;
	
	// the logical operators are tested to make sure one path is masked for each test (1/2 conditions)
	if (a > (a || b))
		r = 3;
	if (a < (a && b)) 
		r = 4;
	if (a <= (a || b))
		r = 5;
	if (a >= (a && b))
		r = 6;
	
	// 3 variables, 1 coupled, per example in AR-06-54, (A and B) op (B nor C)
    if ((a && b) == !(a || c))  
		r = 1;
	if ((a && b) != !(a || c)) 
		r = 2;
	if ((a && b) > !(a || c)) 
		r = 3;
	if ((a && b) <  !(a || c)) 
		r = 4;
	if ((a && b) <= !(a || c)) 
		r = 5;
	if ((a && b) >= !(a || c)) 
		r = 6;
	
	return r;
}

/*=========================================================================*//**
 ** \brief     Coupled short-circuit operators - 2 var basic (A first)
 ** \satisfies A-6 (partial 1/4) Coupled short-circuit operators
 ** \details   Exercises short-circuited logical AND behavior where the second
 **            operand is evaluated only if the first operand is true.  Verifies
 **            that coverage tools correctly represent masked paths created by
 **            short-circuit semantics. From AR-06-54 document, section 
 **            A.1.2.2.3 Example 1 'A_AND_THEN_B(bool A, bool B)'
 *//*=========================================================================*/

void A6_1(bool A, bool B) /* from AR-06-54 document, section A.1.2.2.3 Example 1 'A_AND_THEN_B(bool A, bool B)' */
{
	int a = FALSE;
    if (A && B )       // Similar to using Ada's 'if A and then B' to force short circuiting
	{        
        a = 11;        
    } 
	else 
	{
        a == 12;         
    }
}

/*=========================================================================*//**
 ** \brief     Coupled short-circuit operators - 2 var basic (B first)
 ** \satisfies A-6 (partial 2/4) Coupled short-circuit operators
 ** \details   Exercises short-circuit behavior with operand order reversed,
 **            verifying that coverage tools correctly track evaluation masking
 **            when the left operand determines whether the right operand is
 **            executed. From AR-06-54 document, section A.1.2.2.3 Example 1 \
 **            'B_AND_THEN_A(bool A, bool B)'
 *//*=========================================================================*/

void A6_2(bool A, bool B) /* from AR-06-54 document, section A.1.2.2.3 Example 1 'B_AND_THEN_A(bool A, bool B)' */
{
 	int a = FALSE;
    if (B && A)       // Similar to using Ada's 'if B and then A' to force short circuiting
	{        
        a = 21;       
    } 
	else 
	{
        a = 22;         
    }
}

/*=========================================================================*//**
 ** \brief     Coupled short-circuit operators-2 var multi cond nested,1 missing
 ** \satisfies A-6 (partial 3/4) Coupled short-circuit operators
 ** \details   Exercises a three-input majority voter implemented using short-
 **            circuited logical AND and OR operators.  Verifies that coverage
 **            tools correctly represent multi-operand short-circuit behavior in
 **            coupled Boolean expressions.
 *//*=========================================================================*/

void A6_3(bool A, bool B, bool C) /* from AR-06-54 document, section A.1.2.2.3 Example 2 'Majority3_SC(bool A, bool B, bool C)' */
{
    // Implements 3-input majority voter using C analogy to Ada's 'AND THEN and OR ELSE' to indicate short circuiting with
	// Coupled Boolean values; C short circuits the '&&' and '||' automatically
	int a;
	
    if ( (A && B) ||
         (B && C) ||
         (C && A) )
    {
        a = 11;   
    } else {
        a = 12;  
    }
}

/*=========================================================================*//**
 ** \brief     Coupled short-circuit operators-3 var multi cond nested,0 missing
 ** \satisfies A-6 (partial 4/4) Coupled short-circuit operators
 ** \details   Provides an alternate instance of the three-input majority voter
 **            using short-circuited logical operators.  Ensures consistent
 **            coverage behavior across repeated coupled Boolean structures.
 *//*=========================================================================*/

void A6_4(bool A, bool B, bool C) /* from AR-06-54 document, section A.1.2.2.3 Example 2 'Majority3_SC(bool A, bool B, bool C)' */
{
    // Implements 3-input majority voter using C analogy to Ada's 'AND THEN and OR ELSE' to indicate short circuiting with
	// Coupled Boolean values; C short circuits the '&&' and '||' automatically, declared again here to test alternate coverage via main()
	int a;
	
    if ( (A && B) ||
         (B && C) ||
         (C && A) )
    {
        a = 11;   
    } else {
        a = 12;  
    }
}

/*=========================================================================*//**
 ** \brief     Non-tree decision structures
 ** \satisfies A-8 Non-tree decision structures
 ** \details   Exercises a non-tree-like Boolean decision structures containing 
 **            tree 'loops' at beginning, middle and end of the tree.  Prior to
 **            GCC 14, this test would incorrectly show MCDC coverage for 3 
 **            calls rather than 4. Exercise the most notable change in GCC 14.
 *//*=========================================================================*/

int A8_1(int a, int b, int c, int d, int e)   /* non tree like  */
                        /* prior to GCC 14, this test incorrectly showed correct coverage             */
{
	int r = a; /* return value */
	if ((b && c) || a)  /* one loop at top of bdd */
						/* this is a non tree-like function that showed complete coverage when      */
	                    /* called with (1,0,1), (0,1,0), and (0,1,1); not (0,0,1) -                 */
						/* so this should show incomplete coverage when called with only those 3    */
	{
        r = b;
	}
	if (d && ((b && c) || a))  /* one loop in middle of bdd */

	{
        r = b;
	}
	if (d && ((b && c) || a) && e)  /* two loops in middle of bdd */
	{
        r = b;
	}

	return (r);
}

/*=========================================================================*//**
 ** \brief     Main program - coverage exerciser
 ** \return    0 if terminates without errors, -1 otherwise
 ** \details   Calls or intentionally does not call the set Level A, B, or C 
 **            coverage tests within this file.  As a result of this gcov output
 **            will be generated to show coverage statistics.  The function 
 **            selectively calls test functions to demonstrate both covered and 
 **            intentionally uncovered code paths,
 **            including switch statements, short-circuit expressions, ternary
 **            operators, multi-line and single-line basic blocks, indentation
 **            variations, compiler optimization effects, Boolean logic
 **            constructs, relational operators, coupled and uncoupled
 **            conditions, and non-tree decision structures.  This execution,
 **            coupled with the gcc_testsuite_gcov-19 form the entirety of the
 **            tests needed to verify gcc mcdc tools against the corresponding
 **            requirements set.
 *//*=========================================================================*/

int main(void)
{
	int a= 0;
	bool T = (1 == 1);   // Used when adapting Ada tests from AR-06-54 
    bool F = (2 == 3);   // Used when adapting Ada tests from AR-06-54 

    /* ---------------- Level C tests --------------------------------*/
	
	/* C2_2 not called to show no coverage */
	
	/* C5_1 is not called to show no coverage */
	
	a = C4_1(1); /* empty else should show uncovered */
	
	/* switch statement tests */
	a = C5_2(0); /* one case covered  */
	a = C5_3(3); /* default statement should be covered */
	a = C5_4(0); /* no breaks, should show 100% coverage */
	
	/* Duff's Algorithms switch statement tests */
	int data[8] = {1,2,3,4,5,6,7,8};
	a = C5_5(data, 0);  // case 0
	a = C5_6(data, 1);  // case 1
	a = C5_7(data, 2);  // case 2
	a = C5_8(data, 3);  // case 3
	a = C5_9(data, 4);  // case 0 (full loop)
	a = C5_10(data, 7);	// case 3 (multi-iteration)
	
	C10_1(0, 1);
	C10_2(1, 1);
	
	a = C11_1(0);
	
	C12_1();
	C13_1();
	a = C14_1(a);	
	C15_1();
	
	/* optimization tests */	
	/* C16_1 not called to show no coverage */
	/* C16_2 not called to show no coverage,  */
	/* C17_1(); */
	/* C17_2(); */
	a = C18_1(0);
	a = C18_2(-1);
	a = C18_3(0);
	a = C18_4(-1);
	/* C19_1(); not called to show coverage with optimized code removed */
	/* C19_2(); not called to show no coverage without optimized code removed*/
		
	C20_1();      /* macro testing */
	C21_1();      /* continue statement */
	C22_1();      /* comma operator */
	a = C23_1(a); /* conditional compile */

	/* ---------------- Level B tests --------------------------------*/

	B1_1(); 
	a = B2_1(1);
	a = B3_1();
	a = B4_3();
	a = B6_1(0, 1);
	a = B8_1(a);
	a = B11_1(1);
	a = B11_2(0);
	
	/* ---------------- Level A tests --------------------------------*/

	A4_1(F, F);  /* should show full MC/DC */
    A4_1(F, T);
    A4_1(T, F);
    A4_1(T, T);
	
    A4_2(F, F, T);  // call (1)  /* Per AR-06-54: If only the first 4 calls are made,                     */
	                             /* "MSM will find that the first 'and' has not been */
	                             /* adequately covered because there is never an outcome of True from it. */ 
    A4_2(F, T, T);  // call (2)
    A4_2(T, F, T);  // call (3)
    A4_2(T, F, F);  // call (4)
	A4_2(T, T, F);  // call (5) /* calls 5 and 6 added for full Masking MCDC coverage */
	A4_2(F, T, F);  // call (6)
	

	a = A2_1(1, 0);	  /* identical to B6_1, but called with inverse to test other side of conditionals in relational operators */

	a = A5_1(T, T, F); /* one, two, three variable coupled relational operator tests, combined with Boolean operators */
	a = A5_1(F, T, F);
    a = A5_1(T, F, F);	
	a = A5_1(T, F, T);
	
	A6_1(T, T);
	A6_1(T, F);
	A6_1(F, F);
	A6_2(T, T);
	A6_2(T, F);
	A6_2(F, F);
	A6_3(F, F, T);
	A6_3(F, T, T);
	A6_3(T, F, T);
	A6_3(T, F, F);
	A6_4(T, T, F);
	A6_4(F, T, T);
	A6_4(T, F, T);
	A6_4(T, F, F);
	A6_4(F, T, F);
	A6_4(F, F, T);
	
	a = A8_1(1, 0, 1, 1, 1);
	a = A8_1(1, 1, 0, 1, 1);
	a = A8_1(0, 1, 1, 1, 1);
		
	return (0);
}