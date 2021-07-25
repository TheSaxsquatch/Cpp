## Unit Tests:

### 1.	HaveMaxSizeGreater
#### a.	For this test, the instructions were to create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries. I created a separate check to verify when the test is true as entries are added. Each step will verify the size following each addition to ensure that there is the correct amount is in each grouping.

### 2.	HaveCapacityGreater
#### a.	For this test, the instructions were to create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries. I used a similar approach to above.

### 3.	VerifyResizingIncreases
#### a.	For this test, the instructions were to create a test to verify resizing increases the collection. This test was done by verifying the size and then adding to that size. Once this process was completed, the test verified the size once again.

### 4.	VerifyResizingDecreases
#### a.	For this test, the instructions were to create a test to verify resizing decreases the collection. This test was created like that above, just with decreasing the size.

### 5.	VerifyResizingDecreasesToZero
#### a.	For this test, the instructions were to create a test to verify resizing decreases the collection to zero. This test was done by verifying the size, setting the new size to zero, and verifying the new size.

### 6.	ClearErasesCollection
#### a.	For this test, the instructions were to create a test to verify clear erases the collection. Like those above, the size was verified, clear was run, and it was verified that the collection was truly cleared.

### 7.	EraseClearsCollection
#### a.	For this test, the instructions were to create a test to verify erase(begin,end) erases the collection. Like those above, the size was verified, erase was run, and it was verified that the collection was truly cleared.

### 8.	ReserveIncreasesCapacityNotSize
#### a.	For this test, the instructions were to Create a test to verify reserve increases the capacity but not the size of the collection. In a process similar to above, I chose to verify the size of the collection. 

### 9.	OutOfRangeExceptionVerify
#### a.	For this test, the instructions were to create a negative test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds. I used this to verify the range of the collection.

### 10.	EntryRemoveReducedSize
#### a.	For this test, I stuck with a removal test and chose to remove two entries from the vector and then populated a size check. I wanted to implement the pop_back function.

### 11.	ClearAndAtVectorTest
#### a.	For this test, I added to the clear vector test so that I would be able to create a negative test. I created a test to access the first element after clearing the collection.


## Steps:

#### First I took a moment to understand what was required of me in the assignment. I looked through all of the TODO portions of the code and decided on names for the tests that would be identifiable in terms of what they were to accomplish. Then I chose the last two tests I was going to create. In this process, I chose tests that built off of the other tests, so that I would have an idea of where I was going with my code. Next, I started at the top of the TODO section and began my coding process. I was sure to evaluate what I needed to use for each test and implemented the ASSERT or EXPECT accordingly. I also made sure to implement the try/catch mechanism correctly for the negative tests and implement the exception correctly.


