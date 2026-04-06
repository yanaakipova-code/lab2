
class Exception{
private:
    const char* m_message;
public:
    Exception(const char* message):  m_message(message){}\
    virtual ~Exception() = default;
    virtual const char* what() const {
        return m_message;
    }
};

class OutOfRangeException: public Exception{
public:
    OutOfRangeException(const char* message) : Exception(message) {}
};

class InvalidArgumentException: public Exception{
public:
    InvalidArgumentException(const char* message): Exception(message){}
};

class EmptySequenceException: public Exception{
public:
    EmptySequenceException(const char* message): Exception(message){}
};

class LengthMismatchException : public Exception {
public:
    LengthMismatchException(const char* message) : Exception(message) {}
};

class NullPointerException : public Exception {
public:
    NullPointerException(const char* message) : Exception(message) {}
};