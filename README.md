# LibJsonRpc

## Structure
> The layout of this project closely
> follows the 'Canonical Project Structure'
> as specified in document P1204R0.

## Definitions
> This project aims for consistency
> with the definitions in the following documents:
> > * RFC 2119
> > * RFC 4627
> > * JSON-RPC 2.0 Specification

## Objectives
> * Easily send and receive synchronous or asynchronous requests and responses to a server using the JSON-RPC 2.0 protocol.
> * Make no assumptions or decisions on how the user wishes to handle JSON.
> * Minimal performance cost.
> * Take advantage of batch requests as described in the JSON-RPC 2.0 specification.

## Features
> JSON-RPC 2.0 over:
> > * HTTP/S