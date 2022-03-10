#!/usr/bin/perl
##############################################################
## driver.pl - 15-411 Lab4 Driver                           ##
##                                                          ##
## Driver for CMU, 15-411 Compiler Design, Fall 2007,08,09  ##
## Functionality:  compiling compiler, compiling tests,     ##
##                 validating tests with reference compiler ##
##                 testing compiler                         ##
##                                                          ##
##############################################################

use strict 'vars';
use Getopt::Std;

use lib ".";
use Driverlib;
use Driverlib qw(printd);
use Driverlib qw(system_with_timeout);

use strict;
use File::Copy;
use File::Basename;
use FileHandle;
use Socket;
use POSIX qw(ctime);
use POSIX qw(mktime);
use POSIX qw(strftime);
use POSIX qw(ceil);
use POSIX ":sys_wait_h";
use POSIX ":signal_h";

###
# Declarations and Initialization
#
my $userid;			# -u <userid>, if specified or ""
# my $debug;			# -d <debug> (default 0)
my $skip_make;			# -s, skip generation of compiler
my $validate_tests;		# -t <dir>, validate test files with ref.comp.
my $submit_files;               # -f, submit files for ref.comp on autolab
my @testfiles;			# files... (default ../tests0)
my $default_tests;		# if files were given explicitly or not
my $version;			# -v version, hidden flag for autograder
my $autograded;			# -A, hidden flag for autograder

my $MAKEFILE = "Makefile";	# name of file to make compiler
my $MAKE_TIMEOUT = 40;		# timeout for making compiler
my $COMPILER = "l4c";		# name of compiler to generate
my $COMPILER_EXEC = "bin/l4c";	# compiler executable
my $REF_COMPILER = "/usr0/autolab/autolab/courses/15411-f09/labs/lab4tests/bin/l4c";
				# reference compiler
my $LEXT = "l4";		# source filename extension
my $GCC = "gcc -m64";		# gcc executable and default flags
my $RT = "l4rt.c";		# runtime system for linking against asm file

my $COMPILER_TIMEOUT = 30;	# timeout for running compiler
my $GCC_TIMEOUT = 5;		# timeout for GCC on asm file
my $RUN_TIMEOUT = 5;		# timeout for running compiled executable

my $TESTS_DIR = "../tests";     # directory with student's test suite
my $TESTS0_DIR = "../tests0";	# directory with standard test suite 0
my $TESTS1_DIR = "../tests1";	# directory with standard test suite 1

my $MAX_SCORE0 = 10;		# maximal score for compiler, test suite 0
my $MAX_SCORE1 = 80;		# maximal score for compiler, test suite 1
my $MAX_VALIDATE_SCORE = 10;	# maximal score for test case validation
my $MIN_TESTS = 20;		# minimum number of tests to submit
my $TESTS1_N = 5;		# first 5 failing suite 1 tests
my $TESTS1_PTS = 2;		# are worth 2 points each
my $TESTS1_MIN = 45;		# no score below 45

my $num_tried = 0;		# number of tests tried
my $num_succeeded = 0;		# number of tests succeeded
my $num_tried0 = 0;		# number of tests0 tried
my $num_succeeded0 = 0;		# number of tests0 succeeded
my $score0 = 0;			# score for suite 0
my $num_tried1 = 0;		# number of tests1 tried
my $num_succeeded1 = 0;		# number of tests1 succeeded
my $score1 = 0;			# score for suite 1
my $score = 0;			# total score
my $result = "";		# result string for Autolab server

###
# make_compiler
# runs $MAKEFILE and aborts if unsuccessful
#
sub make_compiler {
  my $result;
  if (!-e "$MAKEFILE") {
    die "Makefile does not exist\n";
  }
  if (system_with_timeout($MAKE_TIMEOUT, "make -f $MAKEFILE $COMPILER") != 0) {
    die "make did not succeed\n";
  }
  if (!-e "$COMPILER_EXEC" || !-x "$COMPILER_EXEC") {
    die "compiler does not exist or is not executable\n";
  }
  return 0;
}

###
# asm_suffix(<file>) = <file>.s
#
sub asm_suffix {
  my $file = shift;
  my @fields = split(/[.]/, $file);
  if (scalar @fields == 1) {
    return @fields[0].".s";	# append ".s" if no extension
  } else {
    @fields[@fields-1]="s";	# replace extension with "s" otherwise
    return join('.', @fields);
  }
}

###
# compile_files (<f1>.$LEXT,...,<fn>.$LEXT) = 0
# compile and test given files
#
sub compile_files {
  my $compiler = shift;
  my ($file, $directive, $value, $asm_file, $result, $line);
  if (-e "a.out") { unlink "a.out" or die "could not remove a.out\n"; }
  if (-e "a.result") { unlink "a.result" or die "could not remove a.result\n"; }
  foreach $file (@_) {
    printd(0, "-- Testing file $file --\n");
    ($directive, $value) = &Driverlib::read_testdirective($file);
    $num_tried += 1;
    if ($directive eq "error") {
      if (system_with_timeout($COMPILER_TIMEOUT, "$compiler $file") == 0) {
	printf("Compilation unexpectedly succeeded on $file.\n");
	printf("-- FAIL --\n");
      } else {
	printd(1, "Compilation failed on $file as expected.\n");
	printd(0, "-- OK --\n");
	$num_succeeded += 1;
      }
    } elsif ($directive eq "exception") {
      if (system_with_timeout($COMPILER_TIMEOUT, "$compiler $file") != 0) {
	printf("Compilation unexpectedly failed on $file.\n");
	printf("-- FAIL --\n");
      } else {
	$asm_file = asm_suffix $file;
	if (system_with_timeout($GCC_TIMEOUT, "$GCC $asm_file $RT") != 0) {
	  printf("Compilation of $asm_file failed unexpectedly.\n");
	  printf("-- FAIL --\n");
	} else {
	  $result = system_with_timeout($RUN_TIMEOUT, "./a.out");
	  $result = $result & 0x7F;
	  # a value string of "0\n" will be considered == to ""
	  if ($result != 0 && $result != 6 && $value != "") {
	    $value = $value+0;	# convert to integer, for sanity's sake
	    if ($result == $value) {
	      printd(1, "Execution of binary raised appropriate exception $result.\n");
	      printd(0, "-- OK --\n");
	      $num_succeeded += 1;
	    } else {
	      printf("Execution of binary raised inappropriate exception $result; expected $value.\n");
	      printf("-- FAIL --\n");
	    }
	  } elsif ($result != 0 && $result != 6) {
	    printd(1, "Execution of binary raised exception $result.\n");
	    printd(0, "-- OK --\n");
	    $num_succeeded += 1;
	  } elsif ($result == 0) {
	    printf("Execution of binary unexpectedly succeeded.\n");
	    printf("-- FAIL --\n");
	  } elsif ($result == 6) {
	    printf("Out-of-bounds exception: not a legal test case of unsafe execution.\n");
	    printf("-- FAIL --\n");
	  } else {
	    printf("Execution of binary raised inappropriate exception $result.\n");
	    printf("-- FAIL --\n");
	  }
	}
      }
    } elsif ($directive eq "return") {
      if (system_with_timeout($COMPILER_TIMEOUT, "$compiler $file") != 0) {
	printf("Compilation unexpectedly failed on $file.\n");
	printf("-- FAIL --\n");
      } else {
	$asm_file = asm_suffix $file;
	if (system_with_timeout($GCC_TIMEOUT, "$GCC $asm_file $RT") != 0) {
	  printf("Compilation of $asm_file failed unexpectedly.\n");
	  printf("-- FAIL --\n");
	} else {
	  $result = system_with_timeout($RUN_TIMEOUT, "./a.out 2>&1 > a.result");
	  if ($result != 0) {
	    $result = ($result >> 8) & 0x7F; # shift because shell return code
	    printf("Execution of binary unexpectedly failed with exception $result.\n");
	    printf("-- FAIL --\n");
	  } else {
	    # if a.result does not exist, $all_of_file = ''
	    my $all_of_file = &Driverlib::read_file("a.result");
	    if ($all_of_file eq $value) {
	      printd(1, "Correct result\n");
	      printd(0, "-- OK --\n");
	      $num_succeeded += 1;
	    } else {
	      chop $all_of_file;
	      chop $value;
	      printf("Result '$all_of_file' differs from expected answer '$value'.\n");
	      printf("-- FAIL --\n");
	    }
	  }
	}
      }
    } else {
      printf("Incorrect test file format for $file.\n");
      printf("First line must be one of:\n");
      printf("#test return <intvalue>\n");
      printf("#test error\n");
      printf("#test exception\n");
      printf("-- FAIL --\n");
    }
  }
}

sub submit_files {
  my $file;
  foreach $file (@testfiles) {
    printd(0, "-- Testing file $file --\n");
    # my $filebase = basename($file);
    &Driverlib::driver_submitfile($userid, $file);
  }
}

###
# Print usage information
#
sub usage {
    printf STDERR "$_[0]\n";
    printf STDERR "Usage: $0 [-h] [-u userid] [-d n] [-s] [-t] [-f] files...\n";
    printf STDERR "Options:\n";
    printf STDERR "  -h              Print this message\n";
    printf STDERR "  -u userid       Notify autolab server as userid\n";
    printf STDERR "  -d n            Set debug level to n (default 0)\n";
    printf STDERR "  -s              Skip generation of compiler\n";
    printf STDERR "  -t              Validate test files in directory dir\n";
    printf STDERR "  -f              Check test files with reference compiler\n";
    printf STDERR "  files...        Test files\n";
    die "\n";
}

###
# Main program
#

# parse comand line arguments
# since we are going strict on variable names
our($opt_h, $opt_u, $opt_d, $opt_s, $opt_t, $opt_f, $opt_v, $opt_A);
getopts('hu:d:stfv:A');

# here, @ARGV are the remaining, non-switch arguments

if ($opt_h) {
  usage();
}

$userid = "";
$version = 0;
$autograded = 0;		# ?? check

if ($opt_u) {
  $userid = $opt_u;
}

if ($opt_d) {
  $Driverlib::DEBUG = $opt_d + 0;		# ?? convert to a number
}

if ($opt_s) {
  $skip_make = $opt_s;
}

if ($opt_t) {
  $validate_tests = $opt_t;
}

if ($opt_f) {
  $submit_files = $opt_f;
}

# Hidden flag used by the autograder
if ($opt_v) {
  $version = $opt_v;
}

# Hidden flag that indicates that the driver was invoked by an autograder
if ($opt_A) {
  $autograded = 1;
}

if (@ARGV) { # any remaining arguments are filenames
  @testfiles = @ARGV;
  $default_tests = 0;
} else {
  if ($validate_tests) {
    @testfiles = glob "${TESTS_DIR}/*.$LEXT";
  } else {
    @testfiles = glob "${TESTS0_DIR}/*.$LEXT ${TESTS1_DIR}/*.$LEXT";
  }
  $default_tests = 1;
}

###
# Call tests
#

autoflush STDOUT 1;

if (!$skip_make && !$validate_tests && !$submit_files) {
  make_compiler;		# aborts if unsuccessful
}

if ($submit_files) {
  # submitting test files to Autolab server for validation
  # with reference compiler
  submit_files;
  # nothing more to be done
  exit;
}

if ($validate_tests) {
  printf("-- Validating test files --\n");
  compile_files ($REF_COMPILER, @testfiles);
} elsif (!$default_tests) {
  compile_files ($COMPILER_EXEC, @testfiles);
} elsif (-e $TESTS0_DIR) {
  @testfiles = glob "${TESTS0_DIR}/*.$LEXT";
  compile_files ($COMPILER_EXEC, @testfiles);
  $num_tried0 = $num_tried;
  $num_succeeded0 = $num_succeeded;
  if (-e $TESTS1_DIR) {
    $num_tried = 0;
    $num_succeeded = 0;
    @testfiles = glob "${TESTS1_DIR}/*.$LEXT";
    compile_files ($COMPILER_EXEC, @testfiles);
    $num_tried1 = $num_tried;
    $num_succeeded1 = $num_succeeded;
  } else {
    $num_tried1 = 0;
    $num_succeeded1 = 0;
  }
} else {
  die "No standard test files; no score\n";
}

if ($num_tried == 0) {
  die "Nothing done; no score\n";
}

if ($validate_tests) {
  if ($num_tried == 1) {
    if ($num_succeeded == 1) {
      printf("SUCCESS of single file test\n");
    } else {
      printf("FAILURE of single file test\n");
    }
    exit;
  }
  # minumum number of files to hand in is $MIN_TESTS; more are ok
  if ($default_tests && $num_tried < $MIN_TESTS) {
    $num_tried = $MIN_TESTS;
  }
  $score = POSIX::floor($num_succeeded * $MAX_VALIDATE_SCORE / $num_tried);
  printf("Total: $num_succeeded/$num_tried for a score of $score/$MAX_VALIDATE_SCORE for test file validation\n");
  if ($default_tests) {
    $result = "$version:$num_tried:$num_succeeded:$score";
    printf("Driver string :".$result.":\n");
    &Driverlib::driver_post($userid, $result, $autograded);
  }
} else {
  if ($default_tests) {
    if ($num_tried0) {
      $score0 = POSIX::floor($num_succeeded0 * $MAX_SCORE0 / $num_tried0);
      printf("Total: $num_succeeded0/$num_tried0 for a score of $score0/$MAX_SCORE0 for compiler testing with suite 0\n");
      printf("Score0 = $score0 points\n");
    }
    if ($num_tried1) {
      # use piecewise linear scoring for test suite 1
      # first $TESTS1_N tests are worth $TESTS1_PTS each; linear after that to $TESTS1_MIN
      if ($num_succeeded1 >= $num_tried1 - $TESTS1_N) {
      	$score1 = $MAX_SCORE1 - ($num_tried1 - $num_succeeded1) * $TESTS1_PTS;
      } elsif ($num_succeeded >= $TESTS1_MIN) {
      	$score1 = POSIX::floor(($MAX_SCORE1 - $TESTS1_N * $TESTS1_PTS) * ($num_succeeded1 - $TESTS1_MIN) / ($num_tried1 - $TESTS1_N - $TESTS1_MIN));
      } else {
      	$score1 = 0;
      }
      # use linear score to $TESTS1_MIN
      # $score1 = POSIX::floor($MAX_SCORE1 * ($num_succeeded1 - $TESTS1_MIN) / ($num_tried1 - $TESTS1_MIN));
      printf("Total: $num_succeeded1/$num_tried1 for a score of $score1/$MAX_SCORE1 for compiler testing with suite 1\n");
      # form of next line matters for autograder
      printf("Score1 = $score1 points\n");
    }
    $result = "$version:$num_tried0:$num_succeeded0:$score0:$num_tried1:$num_succeeded1:$score1";
    printf("Driver string :".$result.":\n");
  } else {
    $score = POSIX::floor($num_succeeded * 100 / $num_tried);
    printf("Total: $num_succeeded/$num_tried for $score\%\n");
  }
}

# # Send autoresult to server
# # Should depend on test validation or compiler test

# send result string only if
# testing compiler and using default tests

if (!$validate_tests && $default_tests) {
  &Driverlib::driver_post($userid, $result, $autograded);
}

exit;
