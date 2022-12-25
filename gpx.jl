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

N = length(vertexdata[:,1])
L = sqrt(N)
N_TR = size(triangledata)[1]

vtx_x, vtx_y, vtx_z = [ vertexdata[:,i] for i=1:3 ]
vertexvectors = [ vertexdata[i,:] for i=1:N ]

#gbmesh = GeometryBasics.Mesh(faces)

#aax = [ 0, vtx_x[9], vtx_x[9] ]
#aay = [ 0 , vtx_y[9], vtx_y[9] ]
#aaz = [ 0 , vtx_z[9], vtx_z[9]  ]
#aatx = [ vtx_x[9], vtx_x[10] * .1 , vtx_x[21] * .1 ]
#aaty = [ vtx_y[9], 0 , vtx_y[21] * .1 ]
#aatz = [ vtx_z[9], 0 , vtx_z[21] * .1 ]

aax = [ 0 ]
aay = [ 0 ]
aaz = [ 0 ]
aatx = [ vtx_x[9] ]
aaty = [ vtx_y[9] ]
aatz = [ vtx_z[9] ]

function make_fig()
	GLMakie.activate!()

	fig = Figure(resolution=(1800,1800))
	ax = Axis3(fig[1,1], 
		aspect=(1,1,.2), 
		azimuth=-0.4π,
		#elevation=1.2(1/8)π,
		elevation=1.9(1/8)π,
		#aspect=:data,
		perspectiveness=0.5,
		viewmode = :fitzoom
		)
	meshscatter!(ax, vtx_x, vtx_y, vtx_z; markersize=.1)
	#scatterlines!(ax, vtx_x, vtx_y, vtx_z; markersize=1)
	#surface!(ax, tuple)
	poly!(ax, vertexdata, faces, strokewidth=2)
	#lines!(ax, vertexvectors[1], vertexvectors[2], linewidth=2)
	limits!(0, L + (L/1), 0, L + (L/1), -0, 10)
	#arrows!(aax, aay, aaz, aatx, aaty, aatz)
	hidedecorations!(ax)
	hidespines!(ax)
	save("./media/flat.png", fig)
end
make_fig()

println(vtx_x[1])

#println(size(facedata))
#println(Float64.(vertexdata[:,1]))
#println(size(vertexdata))
#println(axes(vertexdata))
#println(sizeof(vertexdata))
#println(typeof(float64(vertexdata[:,1])))
