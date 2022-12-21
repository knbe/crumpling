using GLMakie
using DelimitedFiles
using GeometryBasics

function ll()
	include("gpx.jl")
end

datadir = "./data/"
vertexdata = readdlm(string(datadir, "vertexdata.csv"), ',', Float64)
triangledata = readdlm(string(datadir, "triangledata.csv"), ',', Float64)
faces = readdlm(string(datadir, "faces.txt"), ',', Int64)

N = length(vtx_x)
L = sqrt(N)
N_TR = size(triangledata)[1]

vtx_x, vtx_y, vtx_z = [ vertexdata[:,i] for i=1:3 ]
vertexvectors = [ vertexdata[i,:] for i=1:N ]

#gbmesh = GeometryBasics.Mesh(faces)

function make_fig()
	GLMakie.activate!()

	fig = Figure(resolution=(1800,1800))
	ax = Axis3(fig[1,1], 
		aspect=(1,1,.2), 
		azimuth=-0.4π,
		elevation=1.2(1/8)π,
		#aspect=:data,
		perspectiveness=0.8,
		viewmode = :fitzoom
		)
	meshscatter!(ax, vtx_x, vtx_y, vtx_z; markersize=.1)
	#scatterlines!(ax, vtx_x, vtx_y, vtx_z; markersize=1)
	#surface!(ax, tuple)
	poly!(ax, vertexdata, faces, strokewidth=2)
	#lines!(ax, vertexvectors[1], vertexvectors[2], linewidth=2)
	limits!(0, L + (L/1), 0, L + (L/1), -2, 2)
	hidedecorations!(ax)
	hidespines!(ax)
	save("./media/flat.png", fig)
end
make_fig()

#println(size(facedata))
#println(Float64.(vertexdata[:,1]))
#println(size(vertexdata))
#println(axes(vertexdata))
#println(sizeof(vertexdata))
#println(typeof(float64(vertexdata[:,1])))
