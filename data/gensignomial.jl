using JuMP
using Distributions
import StatsBase
import MathOptInterface as MOI

path = "Simulated"
function genmodel(nvar, order, nterm, boxtype, repeat, box, exponents, path)
   varids = 1:nvar
   model = Model()
   @variables(model, begin
      box[1] <= x[i in varids] <= box[2]
   end)
   terms = []
   for t in collect(1:nterm)
      term = StatsBase.sample(varids, order, replace = false)
      t_exponents = [(rand([-1,1]) > 0 ? 1 : -1) *  rand(Uniform(exponents[1], exponents[2])) for i in term]
      coef = (rand([-1,1]) > 0 ? 1 : -1) *  rand(Uniform(0.1, 1))
      push!(terms, (term, t_exponents, coef))
   end
   @NLobjective(model, Min, sum( t[3] * prod(x[i]^t[2][k] for (k,i) in enumerate(t[1])) for t in terms))
   nl_output =  string(path , "/" , nvar , "_" , order , "_" , nterm, "_", boxtype, "_", repeat, ".nl") 
   io = open(nl_output, "w")
   write(io, model; format = MOI.FileFormats.FORMAT_NL)
   readable_ouput = string(path , "_readable", "/" ,  nvar , "_" , order , "_" , nterm, "_", boxtype, "_", repeat, ".nl") 
   io_ = open(readable_ouput, "w") 
   print(io_, model)
   close(io_)

end

nvars = [10, 20, 30]
orders = [3, 4, 5]
boxes = [(1e-1,1), (1e-1,10)]
nterms = [20, 25, 30]
exponents = (0.5, 5.5)
repeats = [1, 2, 3]

for nvar in nvars
   for order in orders
      for (boxtype, box) in enumerate(boxes)
         for nterm in nterms
            for repeat in repeats
               genmodel(nvar, order, nterm, boxtype, repeat, box, exponents, path)
            end
         end
      end
   end
end