
all:
	protoc --cpp_out=. A/Foo.proto
	protoc --cpp_out=. B/Foo.proto
	c++ -I. -std=c++11 Main.cc A/*.cc B/*.cc `pkg-config --cflags --libs protobuf`
	
clean:
	rm -f a.out A/*.pb.* B/*.pb.*
