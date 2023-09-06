import itertools


h = 3
vertices = [0b000, 0b001, 0b010, 0b100, 0b011, 0b101, 0b110, 0b111]
g1 = [0b000, 0b001, 0b010]
g1.sort()
g2 = [0b011, 0b001, 0b010]
g2.sort()
goods = [g1, g2]

def bitstring(vset):
   if isinstance(vset, list):
      vset_ = ["{0:03b}".format(v) for v in vset]
   else:
      vset_ = "{0:03b}".format(vset)
   return vset_

def printbin(vset):
   print(bitstring(vset))

def processvet(vset):
   vset_ = [v for v in vset]
   vset_.sort()
   return vset_

def setKthBit(v, k, b):
   if b == 1:
      return ((1 << k) | v)
   else:
      return (~(1 << k) & v)

def project(vset, k, b):
   vset_ = [setKthBit(v, k, b) for v in vset]
   return vset_

def isaffinind(vset):
   for k in range(h):
      for b in [0,1]:
         if project(vset, k, b) == vset:
            return True
   return False

def difference(v1, v2):
   sumdiff = 0
   for i in range(h):
      v1i = (v1 >> i) & 1
      v2i = (v2 >> i) & 1
      if v2i < v1i:
         return sumdiff, False
      else:
         sumdiff += v2i - v1i
   return sumdiff, True
       

def ismonotone(vset):
   l = len(vset)
   for i in range(l-1):
      sumdiff, isdiff = difference(vset[i], vset[i+1])
      if not isdiff:
         return False
      elif sumdiff is not 1:
         return False
   return True

def exclude(vset, k):
   vset_ = []
   for v in vset:
      v_ = 0
      j = 0
      for k_ in range(h):
         if k_ is not k:
            if v & (1 << k_) > 0:
               v_ |= (1 << j) 
            j += 1
      vset_.append(v_)
   return vset_

def isgood(vset__):
   vset__.sort()
   if vset__ in goods:
      return True
   else:
      return False

def isprojectgood(vset):
   for k in range(h):
      for b in [0,1]:
         vset1 = project(vset, k, b)
         vset2 = exclude(vset1, k)   
         vset3 = list(dict.fromkeys(vset2))
         if isgood(vset3):
            continue
         else:
            print(k, bitstring(vset), bitstring(vset3))
            return False
   return True             

vsets = itertools.combinations(vertices,4)
vsets = [processvet(vset) for vset in vsets]
nvsets = len(vsets)
print(nvsets)

affinindvsets = []
for vset in vsets:
   if isaffinind(vset):
      printbin(vset)
   else:
      affinindvsets.append(vset)
nvsets = len(affinindvsets)
print("affine:", nvsets)

#monotonevsets = []
#for vset in affinindvsets:
#   if ismonotone(vset):
#      printbin(vset)
#   else:
#      monotonevsets.append(vset)
monotonevsets = affinindvsets
nvsets = len(monotonevsets)
print(nvsets)


goodvsets = []
for vset in monotonevsets:
   if isprojectgood(vset):
      goodvsets.append(vset)
   else:
      printbin(vset)
nvsets = len(goodvsets)
print(nvsets)