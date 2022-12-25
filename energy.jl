using GLMakie
using DelimitedFiles
using GeometryBasics

function kk()
	include("gpx.jl")
end

datadir = "./data/"
vertexdata = readdlm(string(datadir, "HData.csv"), ',', Float64)


