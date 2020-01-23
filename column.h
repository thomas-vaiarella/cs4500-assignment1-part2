  
class Column {
    public:
        Column() {

        }

        ~Column() {
            
        }

        virtual void printType() {
            printf("COLUMN");
        }
};

class BooleanColumn : public Column {
    public:
        BooleanColumn() {

        }

        ~BooleanColumn() {
            
        }

        virtual void printType() {
            printf("BOOL");
        }
};

class IntegerColumn : public Column {
    public:
        IntegerColumn() {

        }

        ~IntegerColumn() {
            
        }

        virtual void printType() {
            printf("INTEGER");
        }
};

class FloatColumn : public Column {
    public:
        FloatColumn() {

        }

        ~FloatColumn() {
            
        }

        virtual void printType() {
            printf("FLOAT");
        }
};

class StringColumn : public Column {
    public:
        StringColumn() {

        }

        ~StringColumn() {
            
        }

        virtual void printType() {
            printf("STRING");
        }
};