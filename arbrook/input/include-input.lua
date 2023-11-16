print("including input")
includedirs {
    basicIncludes
}

dependson { "input"}
filter "configurations:Debug*"
    links {"input-d","gainputstatic-d"}

filter "configurations:Release*"
    links {"input","gainputstatic"}

    filter {}