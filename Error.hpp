#pragma once
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

class ChangeImmutableException: public Exception{
public:
    ChangeImmutableException(const char* message): Exception(message) {}
};

class ZeroStepException: public Exception{
public:
    ZeroStepException(const char* message): Exception(message) {}
};

class MatrixSquereException: public Exception{
public:
    MatrixSquereException(const char* message): Exception(message){}
};

class MatrixSquereSizeException: public Exception{
public:
    MatrixSquereSizeException(const char* message): Exception(message){}
};

class  QueueIsEmptyException: public Exception{
public:
    QueueIsEmptyException(const char* message): Exception(message){}
};

class  NotSetElemException: public Exception{
public:
    NotSetElemException(const char* message): Exception(message){}
};

class  DivisionByZeroException: public Exception{
public:
    DivisionByZeroException(const char* message): Exception(message){}
};

class  ImpossibleToGetInException: public Exception{
public:
    ImpossibleToGetInException(const char* message): Exception(message){}
};