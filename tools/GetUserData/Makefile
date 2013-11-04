CXXSOURCES=./CService.cpp \
		   ./main.cpp \
		   ./StdString.cpp
SOURCES=$(CXXSOURCES)
cxx=cl
CPPFLAGS=/MT -I"../../gusale/lib/jsoncpp-src-0.5.0/include" -I"../../gusale/lib/curl-7.32.0/include" /D "BUILDING_LIBCURL" /D "HTTP_ONLY" -I"F:/cq/boost_1_54_0_32" /D "WIN_PLATFORM" /D "_CRT_SECURE_NO_WARNINGS" /D "UNICODE"
LPFLAGS=/LIBPATH:"../../gusale/lib/jsoncpp-src-0.5.0/build/vs71/release/lib_json" json_vc71_libmt.lib /LIBPATH:"../../gusale/lib/curl-7.32.0/vs/vc8/lib/Release" libcurl.lib /LIBPATH:"F:\cq\boost_1_54_0_32\stage\lib" libboost_regex-vc100-mt-s-1_54.lib 
LIBS=
target:main.o 
	link /out:main.exe *.obj $(LPFLAGS)
main.o:
	$(cxx) -c $(SOURCES) $(CPPFLAGS) /ZI /nologo /W3 /WX- /Od /Oy- /D "WIN32" /D "_CONSOLE"  /Gm /EHsc /Gs /Gd
clean:
	del *.obj main.exe
