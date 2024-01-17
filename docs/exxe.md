# .exxe format for VIM Binary code executables

## How it's made
### Signature
The VEF signature is at the start of a file:
`A0 00` -- Start from A0 00 to CF FF (executable version, current is A000).
`FF 4B FF 90 FF` -- Code section start.
Here is VBC (Vim Binary code).
`FF 4B FF 91 FF` -- Code section end.
`FF 4B FF BD FF` -- Data section start.
Some data for program.
`FF 4B FF BE FF` -- Data section end.

