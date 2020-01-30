//lang::CwC

#pragma once
#include <stdlib.h>
#include <string.h>

/*
 * String - Represents a C-style string 
*/
class String : public Object {
    public:
        char* data;
        // input cannot be null
        String(const char* strInput) {
            this->data = strdup(strInput);
        }

        virtual ~String() {}

        /**
    	 * Returns this String appended by otherStr
    	 * Returned String must be deleted by caller
         * @param other String pointer
        */
        String* concat(String *other) {}

        /**
	 * Returns the size of this String
         */
        size_t size() {}

        /**
         * Compare each character of this String to the other String
         * Return 0 if equal, > 0 if this String has the first greater char,
         * < otherwise
         * @param other String pointer
        */
        virtual int compare(String *other) {}

        /**
	 * Returns the size of this String not including null terminator
	 * Should return size in constant time
        */
        size_t size() {}

        /**
	 * Is this String equal to the given Object?
         * Equality based on char values of each String
         * Overrides equals() from Object
	 * @param otherStr Object pointer
	*/
        bool equals(Object *otherStr) {}

        /**
	 * Returns the hash code for this String
         * Uses hash code algorithm for Java Strings
         * Overrides hashCode() from Object 
        */
        size_t hashCode() {}

        /**
	 * Returns copy of char* representation of this String
        */
        char* strCopy() {}
};
