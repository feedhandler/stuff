
all:
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	mkdir -p a b
	protoc --proto_path=A --cpp_out=a Foo.proto Bar.proto
	protoc --proto_path=B --cpp_out=b Foo.proto Baz.proto
	c++ -g -I. -std=c++11 Main.cc a/*.cc b/*.cc `pkg-config --cflags --libs protobuf`
	
clean:
	rm -rf a.out a b
