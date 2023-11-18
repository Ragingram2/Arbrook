print("including input")
includedirs {
    basicIncludes
}

dependson { "input"}
filter "configurations:Debug*"
    links {"input-d","gainputstatic-d","xinput","Ws2_32"}

filter "configurations:Release*"
    links {"input","gainputstatic","xinput","Ws2_32"}

    filter {}