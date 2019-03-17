w = Integer(35671) ; q = 5 ; R = Zp(w,q) ; print 'Working in ring ',R

# Define function, symbolic expression over integer
f(x) = 12172655049735206766902704703038559858384636896299329359049381021748*x^4 + 11349632906292428218038992315252727065628405382223597973250830870345*x^3 + 9188725924715231519926481580171897766710554662167067944757835186451*x^2 + 8640134917502441100824547249422817926745071806483482930174015978801*x + 170423096151399242531943631075016082117474571389010646663163733960337669863762406085472678450206495375341400002076986312777537466715254543510453341546006440265217992449199424909061809647640636052570307868161063402607743165324091856116789213643943407874991700761651741114881108492638404942954408505222152223605412516092742190317989684590782541294253512675164049148557663016927886803673382663921583479090048005883115303905133335418178354255826423404513286728

# Compute derivate functions
F0 = f.diff(0) ; F1 = f.diff(1)

# Set one integer local solution of f(x) = 0 
r0 = Integer(27020) ; f0r0 = F0(x=r0) ; f1r0 = F1(x=r0)
print 'Is ',r0,' one local solution ? ', (Mod(f0r0,w) == 0) and (Mod(f1r0,w) != 0)

# Get one new local solution from older one at each step of loop
rk = r0 ; wk = Integer(1)

power = 100

for k in range(power-1):  
    print ; print '********** Step ',k,'***********' ; print

    # Compute k-th power of w
    wk = w * wk

    # Compute value of F0 and F1 for rk
    f0rk = Integer(F0(x=rk)) ;# print 'F0(rk) = ', f0rk 
    f1rk = Integer(F1(x=rk)) ;# print 'F1(rk) = ', f1rk 

    # Most important part: 
    #  - f0rk / wk is "Integer" division, removing the w^k factor
    #  - negative (-), multiply and inverse_mod operation in ring R
    t = Integer(f0rk / wk) * inverse_mod(-f1rk,w) ; print t
    rk = rk + Integer(t*wk) ; print rk
    rk = Integer(Mod(rk, wk*w)) # ADDED MODULO

print; print "sol", hex(rk);
