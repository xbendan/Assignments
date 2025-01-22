-- CISC 360 a1, Winter 2025

-- Read the instructions in a1.pdf.

module A1 where

-- Rename this file to include your student ID: a1-studentid.hs
-- Also, add your student ID number after the "=":
student_id :: Integer
student_id = 20344561

-- THIS FILE WILL NOT COMPILE UNTIL YOU ADD YOUR STUDENT ID ABOVE
check_that_you_added_your_student_ID_above = ()

{- Checklist:

   I have read the "Read this first" section,
     including "Reminder", "Try to start early", "Late policy",
     and "Your lowest assignment mark is dropped":

   I have read the "Version control" section:

   I have read the "IMPORTANT: Your file must compile" section:

   I have read the "Document your code" section:

   I have read the "Strive for simplicity" section:

   I have read the "Be careful with library functions" section:

   I have read the "Test cases" section:

   I have added my student ID above: 
-}

{-
Q1:
   cube (m, n)  ==  True
   if and only if
                         3
     n is m cubed  (n = m )

     or
                         3
     m is n cubed  (m = n )

   Hint: Haskell has an exponentiation operator, **,
         but it uses floating-point arithmetic so I wouldn't trust it here.
         The multiplication operator * works on integers (as well as floats).
-}
cube :: Integer -> Integer -> Bool
cube m n = n * n * n == m || m * m * m == n

test_cube1, test_cube2, test_cube3, test_cube4 :: Bool
test_cube1 = (cube 1 (-1)) == False
test_cube2 = (cube 125 5) == True
test_cube3 = (cube (-3) (-27)) == True
test_cube4 = (cube (-3) 27) == False

-- Do all cube tests together
test_cube :: Bool
test_cube = test_cube1 && test_cube2
                       && test_cube3
                       && test_cube4

{-
Q2:
  `spiral': given two integers `dir' and `span',
  returns 1 if `dir' is less than 1,
  and otherwise returns (dir + span) * spiral (dir - 3) (1 - span).
-}

spiral :: Integer -> Integer -> Integer
spiral dir span | dir <  1 = 1
                | dir >= 1 = (dir + span) * spiral (dir - 3) (1 - span)



-- Testing spiral:
test_spiral1, test_spiral2, test_spiral3, test_spiral4, test_spiral :: Bool
test_spiral1 = ((spiral 0 32)    == 1)
test_spiral2 = ((spiral (-32) 5) == 1)
test_spiral3 = ((spiral 13 3)    == 10240)
test_spiral4 = ((spiral 7 600)  == -217060165)

test_spiral  = test_spiral1 && test_spiral2 && test_spiral3 && test_spiral4


{-
Q3.1: 
  spiral_seq n == string containing results of  spiral k 180  for k in 0, ..., n
                  separated by semicolons

  For example,  spiral_seq 2  should return  "1;181;182"
    because spiral 0 180 should return 1,
            spiral 1 180 should return 181,
        and spiral 2 180 should return 182.

  If n < 0, spiral_seq should return the empty string: ""
  
  Hints:
     1. The built-in function  show  converts an integer
        to its (decimal) representation as a string.

     2. You can use the built-in function  ++  to concatenate strings.
          For example, "10" ++ ";" == "10;".

     3. You may find it useful to define a helper function for spiral_seq to call.
-}
spiral_seq :: Integer -> String
spiral_seq n | n <  0 = ""
             | n == 0 = (show spiral 0 180)
             | n >  0 = spiral_seq n - 1 ++ ';' ++ (show spiral n 180)

{-
Q3.2:
  Write two test cases,  test_spiral_seq1  and  test_spiral_seq2,
  that cover the following inputs to spiral_seq:

    1. an integer less than 0
    2. an integer greater than or equal to 0

  See a1.pdf for more information.
-}
test_spiral_seq1 = ((spiral_seq -1) == "")
test_spiral_seq2 = ((spiral_seq 2) == "1;181;182")

test_spiral_seq = test_spiral_seq1 && test_spiral_seq2

{-
Q3.3:
  Do the test cases you wrote in Q3.2 also provide *code coverage*?

  That is, if we run both your tests, does every part of the spiral_seq code
  (and the helper functions you wrote, if any) get used?

  Indicate "Yes" or "No", and *briefly* explain (see a1.pdf for more information):



-}



{-
Q4: Stepping

   Give your answers by filling in the blanks below,
   **including the substitution** in function application steps, as described.

Q4.1: Replace the underlines (_______).

     expression                   justification

     (\y -> y * (6 - y)) 1

  => 1 * (6 - 1)                  by function application with 1 for y

  => 1 * 5                        by arithmetic

  => 6                            by arithmetic



  For full marks, state the substitution in the function application step.
  For example:

  "...                          by function application
                                with 500 for q"
                                     ^^^^^^^^^
                          "500 for q" is the substitution

Q4.2: Replace the underlines (_______).
      Assume a function `incr' has been defined:
-}
decrement x = x - 1
{-
     expression                             justification

     (if True then decrement else (\z -> 9)) 5

  => ______________________________         ________________________________

  => ______________________________         ________________________________


  => ______________________________         ________________________________

  For full marks, state the substitution in all function application steps.

Q4.3: 
  Step the following expression.  (It can only be stepped once.)
  (You cannot directly check the answer in Haskell,
   because Haskell will not print functions.)

     expression                            justification

     (\x -> (\y -> (y + 2, x))) decrement

  => ____________________________          _________________________________

  For full marks, state the substitution in all function application steps.
-}