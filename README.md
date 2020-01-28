# CS4500 Assignment 1, part 2
### Authors: Nishanth Duraiarasu and Ryan Harrigan

Software Development (Vesely's section, TF 1:35-3:15pm)

This is our API design for a Queue structure in CwC. Our Queue class is able to
accommodate both Queues of Objects and Strings, classes which we have defined in
separate header files. The Queue class includes support for adding Objects to a
Queue at the end, removing an Object from the head, pointing to the Object at the
head, returning the size of a Queue, returning the hashCode of a Queue, and
returning whether a Queue is equal to another Queue or not.

Regarding the equals(Object* other) method, our code assumes that two strings
containing equal characters are equal. Two distinct queues both containing the
same String object are equal. Furthermore, two distinct queues containing two
String objects that each have the same characters are still equal.