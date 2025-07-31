#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capa)
    : buffer(), capacity(capa), write_ended(false), read_ended(false), written_bytes(0), read_bytes(0) {}

size_t ByteStream::write(const string &data) {
    size_t restWriteableSpace = remaining_capacity();
    size_t acceptedWrittenData = min(restWriteableSpace, data.length());

    for (size_t i = 0; i < acceptedWrittenData; i++) {
        buffer.push_back(data[i]);
    }

    written_bytes += acceptedWrittenData;
    return acceptedWrittenData;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t acceptedPeek = min(len, buffer.size());
    string out = "";

    for (size_t i = 0; i < acceptedPeek; i++) {
        out += buffer[i];
    }

    return out;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if (len > buffer.size()) {
        set_error();
        return;
    }

    for (size_t i = 0; i < len; i++) {
        buffer.pop_front();
    }

    read_bytes += len;
}

void ByteStream::end_input() { write_ended = true; }

bool ByteStream::input_ended() const { return write_ended; }

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { return buffer.empty(); }

bool ByteStream::eof() const { return buffer.empty() && write_ended ; }

size_t ByteStream::bytes_written() const { return written_bytes; }

size_t ByteStream::bytes_read() const { return read_bytes; }

size_t ByteStream::remaining_capacity() const { return capacity - buffer.size(); }
