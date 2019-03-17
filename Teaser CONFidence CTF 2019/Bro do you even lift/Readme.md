# Bro, do you even lift? (crypto)
## 85 pts

We've got two files, `lift.sage` and `out.txt`:

`lift.sage`:
```python
flag = int(open('flag.txt','r').read().encode("hex"),16)
ranges = int(log(flag,2))
p = next_prime(ZZ.random_element(2^15, 2^16))
k = 100
N = p^k
d = 5
P.<x> = PolynomialRing(Zmod(N), implementation='NTL')
pol = 0

for c in range(d):
    pol += ZZ.random_element(2^ranges, 2^(ranges+1))*x^c


remainder = pol(flag)
pol = pol - remainder
assert pol(flag) == 0

print(p)
print(pol)
```

`out.txt`:
```
35671 // this is our p
12172655049735206766902704703038559858384636896299329359049381021748*x^4 + 11349632906292428218038992315252727065628405382223597973250830870345*x^3 + 9188725924715231519926481580171897766710554662167067944757835186451*x^2 + 8640134917502441100824547249422817926745071806483482930174015978801*x + 170423096151399242531943631075016082117474571389010646663163733960337669863762406085472678450206495375341400002076986312777537466715254543510453341546006440265217992449199424909061809647640636052570307868161063402607743165324091856116789213643943407874991700761651741114881108492638404942954408505222152223605412516092742190317989684590782541294253512675164049148557663016927886803673382663921583479090048005883115303905133335418178354255826423404513286728
// and this the polynomial

```

So, in essence we have some polynomial whose root `mod N` is our flag. Fortunately `N = p^k`, and `p` is known. That's where [Hensel's lifting lemma](https://en.wikipedia.org/wiki/Hensel%27s_lemma) comes into play - it turns out that given a root of a polynomial `mod p^k` you can easily calculate the unique root `mod p^(k+1)`. `p = 35671`, and so we can simply calculate the `mod` of the coefficients and plug the resultin polynomial `mod p` into something like WolframAlpha and get the initial roots - `25020` or `27020`. 

I found [some Sage code](https://ask.sagemath.org/question/9860/solving-polynomial-equations-over-p-adic-fields/?answer=15332#post-id-15332) online (thanks dom!), I quickly modified it a bit [(`solve.sage:33`)](https://github.com/AltairQ/writeups/blob/master/Teaser%20CONFidence%20CTF%202019/Bro%20do%20you%20even%20lift/solve.sage) - the original code did not take the modulo of the intermediate results, so they grew rapidly, causing the computation to grind to a halt.

The solution derived from initial root `27020` is `0x70347b54683474355f35306d335f68333476795f6c316674316e397d`, which in ASCII is `p4{Th4t5_50m3_h34vy_l1ft1n9}`.
