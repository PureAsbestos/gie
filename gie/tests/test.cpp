//
// Created by alex on 11/17/18.
//

#include <catch2/catch.hpp>

#include <gie/Node.h>
#include <gie/Program.h>

#include <boost/python.hpp>

#include <cassert>
#include <vector>

#include <iostream>

TEST_CASE("GIE API tests", "[program]")
{
    Program program;
    NodeId castToString, castToInt;

    program.import("builtins");

    boost::python::object input(10);

    SECTION("single node")
    {

        castToString = program.addNode(Node{{}, {"str", std::vector<std::pair<Argument, std::variant<NodeId, Value>>>{std::make_pair(Argument{"", {"int"}}, std::variant<NodeId, Value>{Value{"int", input}})}}});

        auto result = program.run();

        REQUIRE(std::to_string(boost::python::extract<int>(input)) == std::string{boost::python::extract<std::string>(result.value().m_object)});
    }

    SECTION("two nodes")
    {
        castToInt = program.addNode(Node{{}, {"int", std::vector<std::pair<Argument, std::variant<NodeId, Value>>>{std::make_pair(Argument{"", {"str"}}, std::variant<NodeId, Value>{castToString})}}});

        auto result = program.run();

        REQUIRE(boost::python::extract<int>(input) == boost::python::extract<int>(result.value().m_object));
    }
}